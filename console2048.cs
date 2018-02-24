/*
    This is primitive console version of 2048. 
    My first C# console application.
    Control it via arrows.
    Esc - escape.
    First C# lab
    Ed_Os 2018
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static Random rnd;
        //Screen printing 
        static void PrintGameScreen(int[][] Field, int Score)
        {
            char[][] Screen = new char[32][];

            for (int i = 0; i < 32; i++)
                Screen[i] = new char[64];

            for (int i = 0; i < 4; i++)
                for (int j = 0;j < 4; j++)
                {
                    for (int x = 1 + i * 4; x < 1 + (i + 1) * 4; x++)
                        for (int y = 1 + j * 7; y < 1 + (j + 1) * 7; y++)
                            Screen[x][y] = '.';

                    if(Field[i][j] > 0)
                    {
                        for (int y = 1 + j * 7; y < (j + 1) * 7; y++)
                            Screen[1 + i * 4][y] = Screen[3 + i * 4][y] = '#';

                        Screen[2 + i * 4][1 + j * 7] = Screen[2 + i * 4][6 + j * 7] = '#';

                        int t = (1 << Field[i][j]);

                        for(int z = 0; z < 4 && t > 0; z++)
                        {
                            Screen[2 + i* 4][5 - z + j * 7] = (char)(t % 10 + '0');
                            t /= 10;
                        }
                    }
                }

            Console.Clear();
            Console.WriteLine("Score: " + Score);

            for(int i = 0; i < 32; i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    if (Screen[i][j] == '#')
                    {
                        Console.ForegroundColor = ConsoleColor.DarkGreen;
                    }

                    if ("0123456789".Contains(Screen[i][j]))
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                    }

                    if (Screen[i][j] == '.')
                    {
                        Console.ForegroundColor = ConsoleColor.Yellow;
                    }

                    Console.Write(Screen[i][j]);
                }

                Console.Write('\n');
            }
                
        }

       // One block generation
       static void GenerateNewBlock(ref int[][] Field)
        {
            int t = rnd.Next(1, 16);

            while (true)
            {
                for(int i = 0; i < 4; i++)
                    for(int j = 0; j < 4; j++)
                        if(Field[i][j] == 0)
                        {
                            t--;
                            if(t == 0)
                            {
                                // 4 - 10%, 2 - 90 % almost like the original
                                Field[i][j] = (rnd.Next(1, 10) > 9 ? 2: 1);
                                return;
                            }
                        }
            }
        }
        // Lose checking
        static bool CheckField(ref int[][] Field)
        {
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                {
                    if (Field[i][j] == 0)
                        return true;

                    if(i > 0)
                    {
                        if (Field[i][j] == Field[i - 1][j])
                            return true;
                    }

                    if (i < 3)
                    {
                        if (Field[i][j] == Field[i + 1][j])
                            return true;
                    }

                    if (j > 0)
                    {
                        if (Field[i][j] == Field[i][j - 1])
                            return true;
                    }

                    if (j < 3)
                    {
                        if (Field[i][j] == Field[i][j + 1])
                            return true;
                    }
                }
            return false;
        }
        // Checking if action is unable 
        static bool ActionExisting(ConsoleKeyInfo key, ref int[][] Field, ref int Score)
        {
            bool Done = false;
            int x, y;

            switch (key.Key)
            {
                case ConsoleKey.UpArrow: x = -1; y = 0;break;
                case ConsoleKey.DownArrow: x = 1; y = 0; break;
                case ConsoleKey.LeftArrow: x = 0; y = -1; break;
                case ConsoleKey.RightArrow: x = 0; y = 1; break;
                default: return false;
            }

            for(int i = (x == -1 ? 0: 3); i < 4 && i >= 0; i += (x == -1 ? 1 : -1))
                for(int j = (y == -1 ? 0: 3); j < 4 && j >= 0; j += (y == -1 ? 1: -1))
                {
                    if (Field[i][j] == 0)
                        continue;

                    for (int tx = i + x, ty = j + y; tx < 4 && tx >= 0 && ty < 4 && ty >= 0; tx += x, ty += y)
                    {
                        if (Field[tx][ty] == Field[tx - x][ty - y])
                        {
                            Field[tx][ty]++;
                            Score += (1 << Field[tx][ty]);
                            Field[tx - x][ty - y] = 0;
                            Done = true;
                            break;
                        }

                        if (Field[tx][ty] == 0)
                        {
                            Field[tx][ty] = Field[tx - x][ty - y];
                            Field[tx - x][ty - y] = 0;
                            Done = true;
                        }
                    }
                }

            return Done;
        }
        static void Main(string[] args)
        {
            Console.Clear();
            Console.BackgroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("This is 2048 game! Press something to start ///");
            Console.ReadKey(true);

            //Init
            int[][] Field = new int[4][];
            rnd = new Random();
            for (int i = 0; i < 4; i++)
            {
                Field[i] = new int[4];
                for (int j = 0; j < 4; j++)
                    Field[i][j] = 0;
            }

            GenerateNewBlock(ref Field);
            // Main Game cycle
            int Score = 0;

            while (true)
            {
                GenerateNewBlock(ref Field);
                PrintGameScreen(Field, Score);
                if (CheckField(ref Field) == false)
                {
                    Console.WriteLine("Game over!");
                    break;
                }
                while (true)
                {
                    ConsoleKeyInfo key;

                    if (Console.KeyAvailable == true)
                    {
                        key = Console.ReadKey(true);
                        if (key.Key == ConsoleKey.Escape)
                        {
                            return;
                        }

                        if (ActionExisting(key, ref Field, ref Score))
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}
