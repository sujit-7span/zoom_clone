using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using ZOOM_SDK_DOTNET_WRAP;
using System.Text.Json;

using System.Runtime.InteropServices;

namespace zoom_sdk_demo
{
    public partial class start_join_meeting : Window
    {
        private CancellationTokenSource cts;
        private SoftwareDetectionConfig softwareConfig;

        public start_join_meeting()
        {
            InitializeComponent();
            Application.Current.Exit += OnApplicationExit;

            // Load software list from JSON file
            LoadSoftwareListFromJson("softwareList.json");

            StartDetectionTask();
        }

        private void LoadSoftwareListFromJson(string jsonFilePath)
        {
            try
            {
                string jsonContent = File.ReadAllText(jsonFilePath);

                var options = new JsonSerializerOptions
                {
                    PropertyNameCaseInsensitive = true // Handle case sensitivity
                };
                softwareConfig = JsonSerializer.Deserialize<SoftwareDetectionConfig>(jsonContent, options);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to load software list from JSON file. Error: {ex.Message}");
                Application.Current.Shutdown();
            }
        }


        private void StartDetectionTask()
        {
            cts = new CancellationTokenSource();
            var token = cts.Token;

            Task.Run(() => DetectScreenRecordingSoftware(token), token);
            Task.Run(() => DetectScreenshots(token), token);
        }

        private void DetectScreenRecordingSoftware(CancellationToken token)
        {
            while (!token.IsCancellationRequested)
            {
                try
                {
                    var runningProcesses = Process.GetProcesses();
                    foreach (var process in runningProcesses)
                    {
                        if (softwareConfig?.ScreenRecordingSoftware != null && softwareConfig.ScreenRecordingSoftware.Contains(process.ProcessName.ToLower()))
                        {
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                ShowMessageAndShutdown($"Screen recording software detected: {process.ProcessName}. Some features may be disabled.");
                            });
                            return;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        ShowMessageAndShutdown($"Error detecting screen recording software: {ex.Message}");
                    });
                }

                Thread.Sleep(3000); // Check every 3 seconds
            }
        }

        private void DetectScreenshots(CancellationToken token)
        {
            while (!token.IsCancellationRequested)
            {
                try
                {
                    var runningProcesses = Process.GetProcesses();
                    foreach (var process in runningProcesses)
                    {
                        if (softwareConfig?.ScreenshotSoftware != null && softwareConfig.ScreenshotSoftware.Contains(process.ProcessName.ToLower()))
                        {
                            Application.Current.Dispatcher.Invoke(() =>
                            {
                                ShowMessageAndShutdown($"Screenshot software detected: {process.ProcessName}. Some features may be disabled.");
                            });
                            return;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        ShowMessageAndShutdown($"Error detecting screenshot software: {ex.Message}");
                    });
                }

                Thread.Sleep(3000); // Check every 3 seconds
            }
        }

        private void ShowMessageAndShutdown(string message)
        {
            Application.Current.Properties["ShutdownMessage"] = message;
            Application.Current.Shutdown();
        }

        private void OnApplicationExit(object sender, ExitEventArgs e)
        {
            if (Application.Current.Properties["ShutdownMessage"] is string message)
            {
                MessageBox.Show(message);
            }
        }

        private void RegisterCallBack()
        {
            var meetingService = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap();
            meetingService.Add_CB_onMeetingStatusChanged(onMeetingStatusChanged);
            var participantsController = meetingService.GetMeetingParticipantsController();
            participantsController.Add_CB_onHostChangeNotification(onHostChangeNotification);
            participantsController.Add_CB_onLowOrRaiseHandStatusChanged(onLowOrRaiseHandStatusChanged);
            participantsController.Add_CB_onUserJoin(onUserJoin);
            participantsController.Add_CB_onUserLeft(onUserLeft);
            participantsController.Add_CB_onUserNamesChanged(onUserNamesChanged);
        }

        private void onMeetingStatusChanged(MeetingStatus status, int iResult)
        {
            switch (status)
            {
                case MeetingStatus.MEETING_STATUS_ENDED:
                case MeetingStatus.MEETING_STATUS_FAILED:
                    Show();
                    break;
                default:
                    break;
            }
        }

        private void onUserJoin(Array lstUserID)
        {
            if (lstUserID == null) return;

            for (int i = lstUserID.GetLowerBound(0); i <= lstUserID.GetUpperBound(0); i++)
            {
                UInt32 userId = (UInt32)lstUserID.GetValue(i);
                IUserInfoDotNetWrap user = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap()
                    .GetMeetingParticipantsController().GetUserByUserID(userId);
                if (user != null)
                {
                    string name = user.GetUserNameW();
                    Console.WriteLine(name);
                }
            }
        }

        private void onUserLeft(Array lstUserID)
        {
            // Handle user left event
        }

        private void onHostChangeNotification(UInt32 userId)
        {
            // Handle host change notification
        }

        private void onLowOrRaiseHandStatusChanged(bool bLow, UInt32 userId)
        {
            // Handle low or raise hand status change
        }

        private void onUserNamesChanged(Array lstUserID)
        {
            // Handle user names changed event
        }

        private void button_start_api_Click(object sender, RoutedEventArgs e)
        {
            RegisterCallBack();
            StartMeeting();
        }

        private void button_join_api_Click(object sender, RoutedEventArgs e)
        {
            RegisterCallBack();
            JoinMeeting();
        }

        private void StartMeeting()
        {
            var param = new StartParam
            {
                userType = SDKUserType.SDK_UT_WITHOUT_LOGIN,
                withoutloginStart = new StartParam4WithoutLogin
                {
                    meetingNumber = UInt64.Parse(textBox_meetingnumber_api.Text),
                    userZAK = textBox_AccessToken.Text,
                    userName = textBox_username_api.Text,
                    zoomuserType = ZoomUserType.ZoomUserType_APIUSER
                }
            };

            var err = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap().Start(param);
            if (err == SDKError.SDKERR_SUCCESS)
            {
                Hide();
            }
            else
            {
                MessageBox.Show($"Failed to start meeting. Error: {err}");
            }
        }

        private void JoinMeeting()
        {
            var param = new JoinParam
            {
                userType = SDKUserType.SDK_UT_WITHOUT_LOGIN,
                withoutloginJoin = new JoinParam4WithoutLogin
                {
                    meetingNumber = UInt64.Parse(textBox_meetingnumber_api.Text),
                    userName = textBox_username_api.Text
                }
            };

            var err = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap().Join(param);
            if (err == SDKError.SDKERR_SUCCESS)
            {
                Hide();
            }
            else
            {
                MessageBox.Show($"Failed to join meeting. Error: {err}");
            }
        }

        void Wnd_Closing(object sender, CancelEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }

    public class SoftwareDetectionConfig
    {
        public string[] ScreenRecordingSoftware { get; set; }
        public string[] ScreenshotSoftware { get; set; }
    }
}



//using System;
//using System.ComponentModel;
//using System.Diagnostics;
//using System.Linq;
//using System.Threading;
//using System.Threading.Tasks;
//using System.Windows;
//using ZOOM_SDK_DOTNET_WRAP;
//using System.Runtime.InteropServices;

//namespace zoom_sdk_demo
//{
//    public partial class start_join_meeting : Window
//    {
//        private CancellationTokenSource cts;

//        public start_join_meeting()
//        {
//            InitializeComponent();
//            Application.Current.Exit += OnApplicationExit;
//            StartDetectionTask();
//        }

//        private void StartDetectionTask()
//        {
//            cts = new CancellationTokenSource();
//            var token = cts.Token;

//            Task.Run(() => DetectScreenRecordingSoftware(token), token);
//            Task.Run(() => DetectScreenshots(token), token);
//        }

//        private void DetectScreenRecordingSoftware(CancellationToken token)
//        {
//            // List of common screen recording software process names including Windows default recorder
//            string[] screenRecordingSoftware = new string[]
//            {
//                "obs64",        // OBS Studio
//                "obs32",        // OBS Studio (32-bit)
//                "fraps",        // Fraps
//                "bandicam",     // Bandicam
//                "camstudio",    // CamStudio
//                "screencast",   // Screencast-O-Matic
//                "dxtory",       // Dxtory
//                "snagit",       // Snagit
//                "camtasia",     // Camtasia
//                "screenflow",   // ScreenFlow
//                "gamebar",      // Windows Game Bar
//                "gamebarft",    // Windows Game Bar
//                "gdvr",         // NVIDIA GeForce Experience (ShadowPlay)
//                "amtraydvr",     // AMD Radeon ReLive
//                "screenrec"
//            };

//            while (!token.IsCancellationRequested)
//            {
//                try
//                {
//                    var runningProcesses = Process.GetProcesses();
//                    foreach (var process in runningProcesses)
//                    {
//                        if (screenRecordingSoftware.Contains(process.ProcessName.ToLower()))
//                        {
//                            Application.Current.Dispatcher.Invoke(() =>
//                            {
//                                ShowMessageAndShutdown($"Screen recording software detected: {process.ProcessName}. Some features may be disabled.");
//                            });
//                            return;
//                        }
//                    }
//                }
//                catch (Exception ex)
//                {
//                    Application.Current.Dispatcher.Invoke(() =>
//                    {
//                        ShowMessageAndShutdown($"Error detecting screen recording software: {ex.Message}");
//                    });
//                }

//                Thread.Sleep(3000); // Check every 3 seconds
//            }
//        }

//        private void DetectScreenshots(CancellationToken token)
//        {
//            string[] screenshotSoftware = new string[]
//            {
//                "snippingtool", // Windows Snipping Tool
//                "greenshot",    // Greenshot
//                "lightshot",    // Lightshot
//                "gyazo",        // Gyazo
//                "picpick",       // PicPick
//                "screenrec"
//            };

//            while (!token.IsCancellationRequested)
//            {
//                try
//                {
//                    var runningProcesses = Process.GetProcesses();
//                    foreach (var process in runningProcesses)
//                    {
//                        if (screenshotSoftware.Contains(process.ProcessName.ToLower()))
//                        {
//                            Application.Current.Dispatcher.Invoke(() =>
//                            {
//                                ShowMessageAndShutdown($"Screenshot software detected: {process.ProcessName}. Some features may be disabled.");
//                            });
//                            return;
//                        }
//                    }
//                }
//                catch (Exception ex)
//                {
//                    Application.Current.Dispatcher.Invoke(() =>
//                    {
//                        ShowMessageAndShutdown($"Error detecting screenshot software: {ex.Message}");
//                    });
//                }

//                Thread.Sleep(3000); // Check every 3 seconds
//            }
//        }

//        private void ShowMessageAndShutdown(string message)
//        {
//            // Set the message to be shown in the OnApplicationExit handler
//            Application.Current.Properties["ShutdownMessage"] = message;
//            Application.Current.Shutdown();
//        }

//        private void OnApplicationExit(object sender, ExitEventArgs e)
//        {
//            // Show the message just before the application exits
//            if (Application.Current.Properties["ShutdownMessage"] is string message)
//            {
//                MessageBox.Show(message);
//            }
//        }

//        private void RegisterCallBack()
//        {
//            var meetingService = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap();
//            meetingService.Add_CB_onMeetingStatusChanged(onMeetingStatusChanged);
//            var participantsController = meetingService.GetMeetingParticipantsController();
//            participantsController.Add_CB_onHostChangeNotification(onHostChangeNotification);
//            participantsController.Add_CB_onLowOrRaiseHandStatusChanged(onLowOrRaiseHandStatusChanged);
//            participantsController.Add_CB_onUserJoin(onUserJoin);
//            participantsController.Add_CB_onUserLeft(onUserLeft);
//            participantsController.Add_CB_onUserNamesChanged(onUserNamesChanged);
//        }

//        private void onMeetingStatusChanged(MeetingStatus status, int iResult)
//        {
//            switch (status)
//            {
//                case MeetingStatus.MEETING_STATUS_ENDED:
//                case MeetingStatus.MEETING_STATUS_FAILED:
//                    Show();
//                    break;
//                default:
//                    break;
//            }
//        }

//        private void onUserJoin(Array lstUserID)
//        {
//            if (lstUserID == null) return;

//            for (int i = lstUserID.GetLowerBound(0); i <= lstUserID.GetUpperBound(0); i++)
//            {
//                UInt32 userId = (UInt32)lstUserID.GetValue(i);
//                IUserInfoDotNetWrap user = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap()
//                    .GetMeetingParticipantsController().GetUserByUserID(userId);
//                if (user != null)
//                {
//                    string name = user.GetUserNameW();
//                    Console.WriteLine(name);
//                }
//            }
//        }

//        private void onUserLeft(Array lstUserID)
//        {
//            // Handle user left event
//        }

//        private void onHostChangeNotification(UInt32 userId)
//        {
//            // Handle host change notification
//        }

//        private void onLowOrRaiseHandStatusChanged(bool bLow, UInt32 userId)
//        {
//            // Handle low or raise hand status change
//        }

//        private void onUserNamesChanged(Array lstUserID)
//        {
//            // Handle user names changed event
//        }

//        private void button_start_api_Click(object sender, RoutedEventArgs e)
//        {
//            RegisterCallBack();
//            StartMeeting();
//        }

//        private void button_join_api_Click(object sender, RoutedEventArgs e)
//        {
//            RegisterCallBack();
//            JoinMeeting();
//        }

//        private void StartMeeting()
//        {
//            var param = new StartParam
//            {
//                userType = SDKUserType.SDK_UT_WITHOUT_LOGIN,
//                withoutloginStart = new StartParam4WithoutLogin
//                {
//                    meetingNumber = UInt64.Parse(textBox_meetingnumber_api.Text),
//                    userZAK = textBox_AccessToken.Text,
//                    userName = textBox_username_api.Text,
//                    zoomuserType = ZoomUserType.ZoomUserType_APIUSER
//                }
//            };

//            var err = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap().Start(param);
//            if (err == SDKError.SDKERR_SUCCESS)
//            {
//                Hide();
//            }
//            else
//            {
//                MessageBox.Show($"Failed to start meeting. Error: {err}");
//            }
//        }

//        private void JoinMeeting()
//        {
//            var param = new JoinParam
//            {
//                userType = SDKUserType.SDK_UT_WITHOUT_LOGIN,
//                withoutloginJoin = new JoinParam4WithoutLogin
//                {
//                    meetingNumber = UInt64.Parse(textBox_meetingnumber_api.Text),
//                    userName = textBox_username_api.Text
//                }
//            };

//            var err = CZoomSDKeDotNetWrap.Instance.GetMeetingServiceWrap().Join(param);
//            if (err == SDKError.SDKERR_SUCCESS)
//            {
//                Hide();
//            }
//            else
//            {
//                MessageBox.Show($"Failed to join meeting. Error: {err}");
//            }
//        }

//        void Wnd_Closing(object sender, CancelEventArgs e)
//        {
//            Application.Current.Shutdown();
//        }
//    }
//}
