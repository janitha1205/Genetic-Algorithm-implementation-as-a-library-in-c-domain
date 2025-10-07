#ifndef GA_H
#define GA_H



class GA
{
   public:


    GA(int pop_size,int degree,int num_gens, float mutation_rate,float low,float hi,int* deg,float* n,int ind_len); // Constructor

    float fit_fun(float* veriables);
    int max_val(float* arr);
    float* create_individuals(int num_v);
    float* create_population();
    float* select_parents(int num_p);
    float* cross_overs(float* parents,int num_p);
    float* mutate(float* child,float mutation_rate);
    float* runalgo();


 private:
    int _pop_size;
    int _num_gens;
    int _degree;
    int* _deg;
    float _mutation_rate;
    float* _population;
    float _best_fit_val;
    float* _best_varibles;
    float _low;
    float _hi;
    float* _n;
    int _ind_len;
};

#endif // GA_H
