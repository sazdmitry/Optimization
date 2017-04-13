#include "RandomSearch.h"


RandomSearch::RandomSearch()
{
}


RandomSearch::~RandomSearch()
{
}

void RandomSearch::SetProb(const double& q)
{
	p = (q < 0) ? 0 : (q > 1) ? 1 : q;
}

void RandomSearch::init_funct(MyFunction * f)
{
	current_func = f;
	current_dom = f->GetDom();
	dim = current_dom.GetDim();
}

void RandomSearch::SetStopper(Stopper * s)
{
	stop_method = s;
}

vector<vector<double>> RandomSearch::start_alg(const vector<double>& x0)
{
	if (current_func == 0) { 
		throw std::invalid_argument("Current function is not initialized");
	}
	if (stop_method == 0) {
		throw std::invalid_argument("Stop method function is not initialized");
	}
    vector<vector<double>> track;
    stop_method->reset();
    track.push_back(x0);
	double a;
	vector<double> temp(dim, 1);
    vector<double> current_v = x0;
	vector<double> previous_v(dim);
	double current_value = current_func->evaluate(current_v);
	do {
		a = genAlpha();
		temp = (a > p ? current_func->GetDom() : current_dom).ThrowPoint();
		if (current_value > current_func->evaluate(temp)) {
			current_value = current_func->evaluate(temp);
			current_v.swap(temp);
			previous_v.swap(temp);
			current_dom = a > p ? current_func->GetDom() : current_dom;
			current_dom.Compress(current_v);
            track.push_back(current_v);
		}
	} while (!(stop_method->end_of_search(current_v, previous_v, dim)));
    return track;
}

int RandomSearch::GetCount() const {
    return stop_method->get_counter();
}
