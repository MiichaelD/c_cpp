using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Tuenti5
{
    class Program
    {
        static Dictionary<int, List<string>> _dict = new Dictionary<int, List<string>>();
        static void BuildDictionary()
        {
            var words = File.ReadAllLines("words.txt");
            foreach (var word in words)
            {
                var len = word.Length;
                if (!_dict.ContainsKey(len))
                    _dict.Add(len, new List<string>());
                _dict[len].Add(word);
            }
        }

        static string ExtractPattern(string st)
        {
            MatchCollection mc = Regex.Matches(st, "\n\n(.*)\n\n");
            var r = mc[0].Groups[1].Value.Replace(" ","");
            return r;
        }

        static string SelectAChar(string word, string historyInput)
        {
            var priorities = new string[] {"a", "e", "u", "i", "o"};
            for (int i = 0; i < priorities.Length; i++)
            {
                if (historyInput.ToUpper().IndexOf(priorities[i].ToUpper()) >= 0) 
                    break;

                if (historyInput.ToUpper().IndexOf(priorities[i].ToUpper()) < 0 && 
                    word.ToUpper().IndexOf(priorities[i].ToUpper()) >= 0)
                    return priorities[i];  
            }

            for (int j = 0; j < word.Length; j++)
            {
                if (historyInput.ToUpper().IndexOf(word[j].ToString().ToUpper()) < 0)
                    return word[j].ToString();
            }

            return null;
        }

        static bool IsMatch(string input, string word)
        {
            for (int i = 0; i < word.Length; i++)
            {
                if (input[i] != '_' && input[i] != word[i])
                    return false;
            }
            return true;
        }

        static List<string> MatchList(string pattern, List<string> lst)
        {
            var l = lst.Where(w => IsMatch(pattern, w)).ToList();
            return l;
        }

        static List<string> FilterList(string c, List<string> lst)
        {
            var l = lst.Where(w => w.ToUpper().IndexOf(c.ToUpper()) < 0).ToList();
            return l;
        }

        public static void Main()
        {
            BuildDictionary();

            byte[] data = new byte[1024];
            TcpClient server;

            try
            {
                server = new TcpClient("52.49.91.111", 9988);
            }
            catch (SocketException)
            {
                Console.WriteLine("Unable to connect to server");
                return;
            }
            NetworkStream ns = server.GetStream();

            int recv = ns.Read(data, 0, data.Length);
            var stringData = Encoding.ASCII.GetString(data, 0, recv);
            Console.WriteLine(stringData);

            List<string> cat = null;
            var pattern = "";
            var historyInput = "";
            var input = "";

            while (true)
            {
                if (pattern == "")
                    input = "\n";

                ns.Write(Encoding.ASCII.GetBytes(input), 0, input.Length);
                ns.Flush();

                data = new byte[1024];
                recv = ns.Read(data, 0, data.Length);
                stringData = Encoding.ASCII.GetString(data, 0, recv);

                if (stringData.IndexOf("GAME OVER") >= 0) break;

                var newPattern = ExtractPattern(stringData);
                if (cat == null)
                {
                    cat = _dict[newPattern.Length];
                } 
                else
                {
                    if (newPattern != pattern)
                        cat = MatchList(newPattern, cat);
                    else
                        cat = FilterList(input, cat);
                }
                
                pattern = newPattern;
                if (cat != null && cat.Count > 0)
                {
                    var chosenWord = cat[0];
                    input = SelectAChar(chosenWord, historyInput).ToLower();
                    historyInput += input;
                }
                Console.WriteLine(pattern);
                Console.WriteLine(historyInput);
            }

            Console.Read();
            ns.Close();
            server.Close();
        }

        private static List<string> RemoveWords(string input, List<string> cat)
        {
            cat = cat.Where(w => w.IndexOf(input.ToUpper()) < 0).ToList();
            return cat;
        }
    }
}