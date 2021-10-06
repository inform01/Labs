namespace Task3
{
    class Converter
    {
        private const double DollarToGrivna = 26.5876;
        private const double EuroToGrivna = 31.0185;

        public Converter(double usd, double eur)
        {
            m_usd = usd;
            m_eur = eur;
        }

        public double ConvertToDollars(double grivnas)
        {
			if(m_usd == 0) return 0.0;
            return grivnas / m_usd;
        }
        
        public double ConvertToEuros(double grivnas)
        {
			if(m_eur == 0) return 0.0;
            return grivnas / m_eur;
        }
        
        
        private double m_usd;
        private double m_eur;
    }
}
