namespace Task2
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
}