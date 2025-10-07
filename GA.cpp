#include "GA.h"

GA::GA(int pop_size,int degree,int num_gens, float mutation_rate,float low,float hi,int* deg,float* n,int ind_len)
{
    _n=n;
    _deg=deg;
    _low=low;
    _hi=hi;
    _pop_size=pop_size;
    _degree=degree;
    _num_gens=num_gens;
    _mutation_rate=mutation_rate;
    _ind_len=ind_len;
}
int GA::max_val(float* arr){
    float val=0.0;
    int ind;
    for(int i=0;i<ind_m;i++){
        if (val<arr[i]){
            ind=i;
            val=arr[i];
        }
    }
    return ind;
}
float GA::fit_fun(float* variables){

    float val=0.0;
    for (int i=0;i<_degree;i++){
        val+=_n[i]*(variables[i]**_deg[i]);
    }
    return val;

}
float* GA::create_individuals(int num_v){
    float* val;
    float dif=(_hi-_low);
    for(int i ;i<num_v;i++){
      val[i]=_low+dif*((float)random(100)/100.0);
    }
    return val;



}
float* GA::create_population(){
    return create_individuals(_pop_size);

}

float* GA::select_parents(int num_p){
    float* parents=new float[num_p];
    float sum_p=0.0;
    for(int k=0;k<_pop_size;k++){
       sum_p+= fit_fun(_population[k]);
    }
    float* sel_prob= new float[_pop_size];
    for(int k=0;k<_pop_size;k++){
       sel_prob[k]= fit_fun(_population[k])/sum_p;
    }

    int ind;
    for (int i=0;i<num_p;i++){
        ind=max_val(sel_prob);
        sel_prob[ind]=0.0;
        parents[i]=_population[ind];
    }

    return parents;


}

float* GA::cross_overs(float* parents, int num_p){
    for(int i=0;i<num_p;i++){
        float* parent_set=parents[i];
        for(int j=0;j<_degree;j++){
            parents[i][_degree-j]=parent_set[j];
        }
    }
    return parents;

}
float* GA::mutate(float* individual){
    float sum_val=0.0;
    for(int i=0;i<_degree;i++){

        sum_val+=individual[i];
    }
    for(int i=0;i<_degree;i++){
        if(_mutation_rate>(((float)random(100))/100.0)){
                individual[i]=sum_val-individual[i];

        }

    }
    return individual;
}
float* GA::runalgo(){
    _population=create_population();
    float* best_fit;
    for(int k=0;k<_num_gens;k++){
        int index=(random(5)+1);
        int sz= int(_pop_size/index);
        float* new_gen;
        for(int j=0;j<sz;j++){

            float* parents=select_parents(index);
            float* childs=cross_overs(parents,index);
            for(int h=0;h<index;h++){
                new_gen.append(mutate(childs[h]));
            }

        }
        if (new_gen.size()<_pop_size){
            new_gen.append(mutate(create_individuals(_ind_len)));
        }
        _population=new_gen;
        float* val;
        for (int i=0;i<_pop_size;i++){
            val[i]=fit_fun(_population[i]);
        }
        best_fit[k]=_population[max_val(val)];
    }

    _best_varibles=best_fit[max_val(best_fit)];
    _best_fit_val=fit_fun(_best_varibles);
    return _best_varibles;


}
