#include "Nelder_mead.h"


void Nelder_mead::FindMinMax()
{
	if (current_func == nullptr) {
		throw std::invalid_argument("Current function is not initialized");
	}
	else {

		argmax_idx = argmin_idx = secargmax_idx = 0;
		double tempmin = current_func->evaluate(A[0]);
		double tempmax = tempmin;
		double tempsec_max = tempmin;
		double newtemp;
		for (int i = 1; i < dim + 1; ++i) {
			newtemp = current_func->evaluate(A[i]);
			if (newtemp > tempsec_max)
			{
				if (newtemp > tempmax) {
					secargmax_idx = argmax_idx;
					tempsec_max = tempmax;
					argmax_idx = i;
					tempmax = newtemp;
				}
				else {
					secargmax_idx = i;
					tempsec_max = newtemp;
				}
			}
			else {
				if (newtemp < tempmin)
				{
					argmin_idx = i;
					tempmin = newtemp;
				}
			}
		}
	}
}

Nelder_mead::Nelder_mead()
{
}


Nelder_mead::~Nelder_mead()
{
}

void Nelder_mead::SetCoef(const double a, const double b, const double c, const double d)
{
	alpha = a;
	beta = b;
	gamma = c;
	sigma = d;
}

vector<vector<double>> Nelder_mead::start_alg(const vector<double>& x0)
{
	if (current_func == nullptr) {
		throw std::invalid_argument("Current function is not initialized");
	}
    vector<vector<double>> track;
	///
	double temp = 0;
	/// 
	double distance = 0;
	///
	A[0] = x0;
    track.push_back(x0);
	for (int i = 1; i < dim + 1; ++i) {
		A[i] = x0;
		A[i][i - 1] += 1;
		current_func->GetDom().FixDomain(&A[i]);
	}
    counter=0;
	//main cycle
	do {
		++counter;
		FindMinMax();
		// Step 0. Finding center of mass
		for (int i = 0; i < dim; ++i) {
			temp = 0;
			for (int j = 0; j < dim + 1; ++j) {
				temp += A[j][i];
			}
			temp -= A[argmax_idx][i];
			center_of_mass[i]=(temp / dim);
		}
		current_func->GetDom().FixDomain(&center_of_mass);

		//Step 1. Reflection
		for (int i = 0; i < dim; ++i) {
			reflection[i] = center_of_mass[i] + alpha*(center_of_mass[i] - A[argmax_idx][i]);
		}
		current_func->GetDom().FixDomain(&reflection);
		if ((current_func->evaluate(reflection) < current_func->evaluate(A[secargmax_idx])) && (current_func->evaluate(reflection) > current_func->evaluate(A[argmin_idx]))) {
			A[argmax_idx].swap(reflection);
			//GO TO STEP 0
		}
		else {
			//Step 2. Expansion
			if (current_func->evaluate(reflection) < current_func->evaluate(A[argmin_idx])) {
				for (int i = 0; i < dim; ++i) {
					expansion[i] = center_of_mass[i] + gamma*(reflection[i] - center_of_mass[i]);
				}
				current_func->GetDom().FixDomain(&expansion);
				A[argmax_idx].swap((current_func->evaluate(expansion) <= current_func->evaluate(reflection)) ? expansion : reflection);
				//GO TO STEP 0
			}
			else {
				// Step 3. Compression
				for (int i = 0; i < dim; ++i) {
					compression[i] = center_of_mass[i] + beta*(A[argmax_idx][i] - center_of_mass[i]);
				}
				if (current_func->evaluate(compression) < current_func->evaluate(A[argmax_idx]))	A[argmax_idx].swap(compression); //GO TO STEP 0
				else { //Compression of simplex
					for (int i = 0; i < dim + 1; ++i)
					{
						for (int j = 0; j < dim; ++j)
						{
							if (i != argmin_idx) A[i][j] = A[argmin_idx][j] + (A[i][j] - A[argmin_idx][j])*sigma;
						}
					}
				}
			}
		}
		distance = 0;
		for (int i = 0; i < dim + 1; ++i) {
			temp = (current_func->evaluate(A[i]) - current_func->evaluate(center_of_mass));
			distance += temp*temp;
		}
		distance = sqrt(distance / (dim + 1));
        track.push_back(center_of_mass);
	} while (distance > eps);
    return track;
}

void Nelder_mead::init_funct(MyFunction * f)
{
	current_func = f;
	counter = 0;
	dim = f->GetDom().GetDim();
	A = vector<vector<double>>(dim + 1);
	center_of_mass = vector<double>(dim);
	reflection = vector<double>(dim);
	expansion = vector<double>(dim);
	compression = vector<double>(dim);
}

void Nelder_mead::set_epsilon(double e)
{
	eps = e;
}

int Nelder_mead::get_counter() const
{
	return counter;
}

void Nelder_mead::set_alpha(double a){
    alpha=a;
}
void Nelder_mead::set_beta( double b){
    beta=b;
}
void Nelder_mead::set_gamma(double g){
    gamma=g;
}
void Nelder_mead::set_sigma(double s){
    sigma=s;
}
