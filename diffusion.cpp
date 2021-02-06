
#pragma once
#include <cmath>
#include <stdexcept>
namespace SiriusFM {
	// что делать с трендами? будем считать пока, что тренды более сложные, чем линейные, особого смысла не имеют. Тренды во всех этих случаях будут просто линейными. А волатильности будут разными.

	class DiffusionGBM {
	private:
		double const m_mu;
		double const m_sigma;

	public:
		double mu (double s, double t) {
			return m_mu * s;
		};

		double sigma (double s, double t) {
			return m_sigma * s;
		};

		DiffusionGBM (double a_mu, double a_sigma):
		m_mu(a_mu),
		m_sigma(a_sigma)
		{
			if (m_sigma < 0) throw std::invalid_argument("Invalid Sigma, Diffusion GBM");
		}
	};

	

	
	class DiffusionCEV {
		// beta >= 0
		// sigma > 0
	private:
		double const m_mu;
		double const m_sigma;
		double const m_beta;
	
	public:
		double mu (double s, double t) const {
			return m_mu * s;
		};

		double sigma (double s, double t) const {
			return m_sigma * pow(s, m_beta) ;
		};

		DiffusionCEV(double a_mu, double a_sigma, double a_beta):
		m_mu(a_mu),
		m_sigma(a_sigma),
		m_beta(a_beta)

		{
			if (a_sigma < 0 ) throw std::invalid_argument("Invalid sigma, DiffusionCEV");
			else if (a_beta <0) throw std::invalid_argument("Invalid beta, DiffusionCEV");
		}


	};

	class DiffusionOU {
		//mu = kappa * (theta - s)
		// sigma - default
	private:
		double const m_mu;
		double const m_sigma;
		double const m_theta;
		double const m_kappa;
	
	public:
		double mu (double s, double t) const {
			return m_mu * (m_theta - s);
		};

		double sigma (double s, double t) const {
			return m_sigma * s;
		};

		DiffusionOU (double a_mu, double a_sigma, double a_theta, double a_kappa):
			m_mu(a_mu),
			m_sigma(a_sigma),
			m_theta(a_theta),
			m_kappa(a_kappa)
			{
				if (a_sigma < 0) throw std::invalid_argument("Invalid sigma, DiffusionOU");
				else if (a_kappa < 0) throw std::invalid_argument("Invalid sigma, DiffusionOU");
			}
	};

	class DiffusionLipton {
		private:
			
			double const m_mu;
			double const m_sigma_0;
			double const m_sigma_1;
			double const m_sigma_2;
		
		public:
			
			double mu (double s, double t) const {
			return m_mu * s;
			};

			double sigma (double s, double t) const {
			return m_sigma_0 + m_sigma_1 * s + m_sigma_2 * pow(s,2);
			};

			DiffusionLipton (double a_mu, double a_sigma_0, double a_sigma_1, double a_sigma_2):  
			m_mu(a_mu),
			m_sigma_0(a_sigma_0),
			m_sigma_1(a_sigma_1),
			m_sigma_2(a_sigma_2)
			{
				if ( m_sigma_0 >= 0 && m_sigma_2 >= 0 &&  (pow(m_sigma_1,2) - 4 * m_sigma_0 * m_sigma_2) < 0 ) ;
				else throw std::invalid_argument("Invalid sigmas combination, DiffusionLipton");
			}

	};
	

	class DiffusionCIR {
		// тут theta >0, тренд такой же, + старые constraints
		private:
			double const m_mu;
			double const m_sigma;
			double const m_theta;
			double const m_kappa;
		public:
			double mu (double s, double t) const {
			return m_mu * (m_theta - s);
			};

			double sigma (double s, double t) const {
			return m_sigma * sqrt(s);
			};

			DiffusionCIR (double a_mu, double a_sigma, double a_theta, double a_kappa):
			m_mu(a_mu),
			m_sigma(a_sigma),
			m_theta(a_sigma),
			m_kappa(a_kappa)
			{

				if (a_sigma < 0) throw std::invalid_argument("Invalid sigma, DiffusionOU");
				else if (a_kappa < 0) throw std::invalid_argument("Invalid kappa, DiffusionOU");
				else if (a_theta <0) throw std::invalid_argument("Invalid theta, DiffusionOU");
			}

	};



}

int main() {
using namespace SiriusFM;
};


 