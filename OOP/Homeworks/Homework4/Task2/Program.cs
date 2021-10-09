using System;
namespace Task2
{
    abstract class Figure
    {
        public abstract double getArea();
        public abstract double getPerimeter();
    }

    class Triangle: Figure
    {
        public Triangle(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public override double getPerimeter()
        {
            return a + b + c;
        }
        
        public override double getArea()
        {
            double p = getPerimeter();
            return Math.Sqrt(p / 2 * (p / 2 - a) * (p / 2 - b) * (p / 2 - c));
        }
        
        private double a;
        private double b;
        private double c;
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            var tr = new Triangle(4, 2, Math.Sqrt(20));
            Console.WriteLine(tr.getArea());
        }
    }
}