using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace zoom_sdk_demo
{
    public class HttpRequestHelper
    {
        private static readonly HttpClient _client = new HttpClient();

        // Method to perform a GET request
        public static async Task<string> GetAsync(string url)
        {
            try
            {
                HttpResponseMessage response = await _client.GetAsync(url);
                response.EnsureSuccessStatusCode();
                return await response.Content.ReadAsStringAsync();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"GET request failed: {ex.Message}");
                return null;
            }
        }

        // Method to perform a POST request
        public static async Task<string> PostAsync(string url, string jsonContent)
        {
            try
            {
                HttpContent content = new StringContent(jsonContent, Encoding.UTF8, "application/json");
                HttpResponseMessage response = await _client.PostAsync(url, content);
                response.EnsureSuccessStatusCode();
                return await response.Content.ReadAsStringAsync();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"POST request failed: {ex.Message}");
                return null;
            }
        }

        // Method to perform a PUT request
        public static async Task<string> PutAsync(string url, string jsonContent)
        {
            try
            {
                HttpContent content = new StringContent(jsonContent, Encoding.UTF8, "application/json");
                HttpResponseMessage response = await _client.PutAsync(url, content);
                response.EnsureSuccessStatusCode();
                return await response.Content.ReadAsStringAsync();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"PUT request failed: {ex.Message}");
                return null;
            }
        }

        // Method to perform a DELETE request
        public static async Task<string> DeleteAsync(string url)
        {
            try
            {
                HttpResponseMessage response = await _client.DeleteAsync(url);
                response.EnsureSuccessStatusCode();
                return await response.Content.ReadAsStringAsync();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"DELETE request failed: {ex.Message}");
                return null;
            }
        }
    }
}
