//TASK 2
using System;
using System.Collections.Generic;
using System.IO;
using static System.IO.File;
namespace Homework3
{
    public abstract class Student
    {
        public Student()
        {
            name = "No-name";
        }
        public Student(string name)
        {
            this.name = name;
            this.state = "";
        }
        public string getName()
        {
            return name;
        }

        public string getStates()
        {
            return state;
        }
        public void Relax()
        {
            this.state += "Relax ";
        }
        public void Write()
        {
            this.state += "Write ";
        }
        public void Read()
        {
            this.state += "Read ";
        }

        public abstract void Study();
        
        protected string name;
        protected string state;
    }

    public class BadStudent :Student
    {
        public BadStudent(string name):base(name)
        {
            state += "bad ";
        }

        public override void Study()
        {
            for (int i = 0; i < 5; i++)
            {
                Relax();
            }   
        }
    } 
    
    public class GoodStudent :Student
    {
        public GoodStudent(string name):base(name)
        {
            state += "good ";
        }

        public override void Study()
        {
            Read();
            Write();
            Read();
            Write();
            Relax();
        }
    }

    class Group
    {
        private string groupName;
        private List<Student> studentsList;


        public Group(List<Student> students)
        {
            studentsList = new List<Student>(students);
        }
        public Group(string groupName)
        {
            studentsList = new List<Student>();
            this.groupName = groupName;
        }

        public void AddStudent(Student student)
        {
            studentsList.Add(student);
        }

        public void GetInfo()
        {
            Console.WriteLine("Name of the group: " + groupName);
            for (int i = 0; i < studentsList.Count;++i)
            {
                Console.WriteLine(i+1 + "." + studentsList[i].getName());
            }
        }

        public void GetFullInfo()
        {
            Console.WriteLine("Name of the group: " + groupName);
            for (int i = 0; i < studentsList.Count;++i)
            {
                Console.WriteLine(i+1 + "." + studentsList[i].getName());
                Console.WriteLine("States of student number " + (i + 1) + ":");
                Console.WriteLine(studentsList[i].getStates());
                
            }
        }

    }
    internal class Program
    {
        private const string PathToFile = "/home/oleksandr/Labs/OOP/Homeworks/Homework3/students.txt";
        public static void Main(string[] args)
        {
            Console.WriteLine("START TESTING");
            
            var group = new Group("K27");
            
            //read all students from students.txt file and add to studentList container
            var studentsList = new List<string>();
            string currentLine;
            var streamReader = new System.IO.StreamReader(PathToFile);
            while ((currentLine = streamReader.ReadLine()) != null)
            {
                studentsList.Add(currentLine);
            }
            
            //place all students to group
            for (int i = 0; i < studentsList.Count; ++i)
            {
                var currentStudent = new GoodStudent(studentsList[i]);
                if (i % 3 == 0)
                {
                    currentStudent.Relax();
                }
                else if (i % 3 == 2)
                {
                    currentStudent.Study();
                }
                else if (i % 3 == 2)
                {
                    currentStudent.Write();
                }
                group.AddStudent(currentStudent);
            }
            
            group.GetFullInfo();
        }
    }
}