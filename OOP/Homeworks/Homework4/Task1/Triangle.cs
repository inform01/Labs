using System;
namespace Task1
{
    class Triangle
    {
        public Triangle(double a)
        {
            this.a = a;
            this.b = a;
            this.c = a;
        }
        public Triangle(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }
        protected double a;
        protected double b;
        protected double c;

        public double getPerimeter()
        {
            return (a + b + c);
        }

        public void setSide(UInt16 sideNumber, double newSide)
        {
            if (sideNumber == 1) this.a = newSide;
            else if (sideNumber == 2) this.b = newSide;
            else if (sideNumber == 3) this.c = newSide;
            else throw new Exception("Invalid side number:(");
        }
 
    }

    class EquilateralTriangle: Triangle
    {
        public EquilateralTriangle(double a) : base(a)
        {
            area = (a*a * Math.Sqrt(3)) / 4;
        }

        public double getArea()
        {
            return area;
        }

        private double area;
    }
}