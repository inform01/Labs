using System;
using System.Configuration;

namespace Task1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var eqTr = new EquilateralTriangle(3);
            var tr = new Triangle(1,2,3);
            Console.WriteLine(eqTr.getPerimeter());
            Console.WriteLine(tr.getPerimeter());
        }
    }
}