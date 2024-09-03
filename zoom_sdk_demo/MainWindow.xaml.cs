using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.ComponentModel; // CancelEventArgs
using ZOOM_SDK_DOTNET_WRAP;
using System.Net.Http;
using System.Text.Json;
using System.Security.Claims;

namespace zoom_sdk_demo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        start_join_meeting start_meeting_wnd = new start_join_meeting();
        private string _apiKey;
        private string _orgId;

        public MainWindow()
        {
            UserLogin();
            UserData();
            TodayClasses();
            //ZoomClassJoin();
            InitializeComponent();
        }

        private async void UserLogin()
        {
            var client = new HttpClient();
            var request = new HttpRequestMessage(HttpMethod.Post, "https://enterpriseplanportal-api.edmingle.com/nuSource/api/v1/tutor/login");
            var content = new MultipartFormDataContent();
            content.Add(new StringContent("{\"username\":\"superadmin@edmingle.com\",\"password\":\"test\",\"persistent_login\":true}"), "JSONString");
            request.Content = content;
            var response = await client.SendAsync(request);
            response.EnsureSuccessStatusCode();
            Console.WriteLine(await response.Content.ReadAsStringAsync());
        }

        private async void UserData()
        {
            var client1 = new HttpClient();
            var request1 = new HttpRequestMessage(HttpMethod.Get, "https://enterpriseplanportal-api.edmingle.com/nuSource/api/v1/user/usermeta");
            request1.Headers.Add("apikey", "2d3321d936c68fb99fb880b050023bd9");
            var response1 = await client1.SendAsync(request1);
            response1.EnsureSuccessStatusCode();
            Console.WriteLine(await response1.Content.ReadAsStringAsync());
        }

        private async void TodayClasses()
        {
            var client2 = new HttpClient();
            var request2 = new HttpRequestMessage(HttpMethod.Get, "https://enterpriseplanportal-api.edmingle.com/nuSource/api/v1/student/classes/period?date=08%20Nov%202023");
            request2.Headers.Add("apikey", "2d3321d936c68fb99fb880b050023bd9");
            request2.Headers.Add("ORGID", "5131");
            var response2 = await client2.SendAsync(request2);
            response2.EnsureSuccessStatusCode();
            Console.WriteLine(await response2.Content.ReadAsStringAsync());
        }

        private async void ZoomClassJoin()
        {
            var client3 = new HttpClient();
            var request3 = new HttpRequestMessage(HttpMethod.Post, "https://enterpriseplanportal-api.edmingle.com/nuSource/api/v1/liveclass/join/<attendanceId>");
            request3.Headers.Add("apikey", "2d3321d936c68fb99fb880b050023bd9");
            request3.Headers.Add("ORGID", "5131");
            var response3 = await client3.SendAsync(request3);
            response3.EnsureSuccessStatusCode();
            Console.WriteLine(await response3.Content.ReadAsStringAsync());
        }

        //callback
        public void onAuthenticationReturn(AuthResult ret)
        {
            if (ZOOM_SDK_DOTNET_WRAP.AuthResult.AUTHRET_SUCCESS == ret)
            {
                start_meeting_wnd.Show();
            }
            else//error handle.todo
            {
                Show();
            }
        }
        public void onLoginRet(LOGINSTATUS ret, IAccountInfo pAccountInfo, LOGINFAILREASON reason)
        {
            //todo
        }
        public void onLogout()
        {
            //todo
        }
        private void button_auth_Click(object sender, RoutedEventArgs e)
        {
            //register callback
            ZOOM_SDK_DOTNET_WRAP.CZoomSDKeDotNetWrap.Instance.GetAuthServiceWrap().Add_CB_onAuthenticationReturn(onAuthenticationReturn);
            ZOOM_SDK_DOTNET_WRAP.CZoomSDKeDotNetWrap.Instance.GetAuthServiceWrap().Add_CB_onLoginRet(onLoginRet);
            ZOOM_SDK_DOTNET_WRAP.CZoomSDKeDotNetWrap.Instance.GetAuthServiceWrap().Add_CB_onLogout(onLogout);
            //
            ZOOM_SDK_DOTNET_WRAP.AuthContext param = new ZOOM_SDK_DOTNET_WRAP.AuthContext();
            param.jwt_token = textBox_apptoken.Text;
            ZOOM_SDK_DOTNET_WRAP.CZoomSDKeDotNetWrap.Instance.GetAuthServiceWrap().SDKAuth(param);
            Hide();
        }

        void Wnd_Closing(object sender, CancelEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}
