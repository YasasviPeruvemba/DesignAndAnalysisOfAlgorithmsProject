#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back

int main()
{
	map <string,double> start_probability;
  map <pair<string,string>,double> transition_probability;
  map <pair<string,string>,double> emmission_probability;

  vector <string> states;
  
  int nostates;
  
  //The possible hidden states --- change those here
  states.pb("Healthy");
  states.pb("Fever");
 
  vector<string> obs;
  int noobs;
  cout<<"Enter number of observable states : ";
  cin>>noobs;
  string observe;
  double str_prob;
  vector <string> observable;
  cout<<"Enter the observable states : "<<endl;
  
  //Getting all of  the observable states
  for(int i=0;i<noobs;i++){
    cin>>observe;
    observable.pb(observe);
  }
  cout<<endl;

  //Getting the starting probablities for the hidden states
  for(int i=0;i<states.size();i++){
    cout<<"Enter starting probablity of "<<states[i]<<": ";
    cin>>str_prob;
    start_probability[states[i]] = str_prob;
  }
  cout<<endl;

  //Getting the transition probablities for the states
  cout<<"Enter transition probablities for : "<<endl;
  double trans_prob;
  states.pb("E");
  for(int i=0;i<states.size();i++){
    for(int j=0;j<states.size();j++){
      cout<<states[i]<<"->"<<states[j]<<" : ";
      cin>>trans_prob;
      transition_probability[mp(states[i],states[j])] = trans_prob;
    }
  }
  cout<<endl;

  //Getting the Emmission probabilities
  cout<<"Enter emmission probabilities for : "<<endl;
  double emm_prob;
  for(int i=0;i<states.size();i++){
    for(int j=0;j<observable.size();j++){
      cout<<states[i]<<"->"<<observable[j]<<" : ";
      cin>>emm_prob;
      emmission_probability[mp(states[i],observable[j])] = emm_prob;
    }
  }
  cout<<endl;

  //Getting the observed sequence
  int obsfinal;
  cout<<"Enter the total length of observed states : ";
  cin>>obsfinal;
  cout<<"Enter the observed states : "<<endl;
  for(int i=0;i<obsfinal;i++){
    cin>>observe;
    obs.pb(observe);
  }
  states.pop_back();
  cout<<endl;

  //Forward Part

  vector <vector <double>> fwd;
  vector <double> f_prev;
  double prev_f_sum;
  for(int i=0;i<obs.size();i++){
  	vector <double> f_curr;
  	for(int st=0; st<states.size();st++){
  		if(i==0){
  			prev_f_sum = start_probability[states[st]];
        //cout<<prev_f_sum<<"\t";
  		}
  		else{
        prev_f_sum = 0;
  			for(int k=0;k<states.size();k++){
  				prev_f_sum += f_prev[k]*transition_probability[mp(states[k],states[st])];
  			  //cout<<prev_f_sum<<"\t";
        }
  		}
  		f_curr.pb(emmission_probability[mp(states[st],obs[i])]*prev_f_sum);
  		cout<<"Forward Probablity for "<<states[st]<<" : "<<f_curr[st]<<endl;
  	}
  	fwd.pb(f_curr);
  	f_prev = f_curr;
  }

  double p_fwd=0;
  string endstate = "E";
  
  for(int k=0;k<states.size();k++){
  	p_fwd += f_prev[k]*transition_probability[mp(states[k],endstate)];
  }
  cout<<"Forward Probablity Final : "<<p_fwd<<endl;

  //Backward Part

  vector <vector <double>> bkw;
  vector <double> b_prev;
  vector <string> revobs;
  revobs.pb("");
  for(int i=0;i<obs.size()-1;i++){
    revobs.pb(obs[obs.size()-i-1]);
  }
  for(int i=0;i<revobs.size();i++){
    vector <double> b_curr;
    for(int st=0;st<states.size();st++){
      if(i==0){
        b_curr.pb(transition_probability[mp(states[st],endstate)]);
        cout<<"Backward Probablity for "<<states[st]<<" : "<<b_curr[st]<<endl;
      }
      else{
        double b_sum=0;
        for(int l=0;l<states.size();l++){
          b_sum += transition_probability[mp(states[st],states[l])]*emmission_probability[mp(states[l],revobs[i])]*b_prev[l];
        }
        b_curr.pb(b_sum);
        cout<<"Backward Probablity for "<<states[st]<<" : "<<b_sum<<endl;
      }
    }
    vector <double> a;
    bkw.pb(b_curr);
    b_prev = b_curr;
  }

  double p_bkw=0;
  for(int l=0;l<states.size();l++){
    p_bkw += start_probability[states[l]]*emmission_probability[mp(states[l],obs[0])]*b_prev[l];
  }
  cout<<"Backward Probability Final : "<<p_bkw<<endl;

  //Merging both results
  vector <vector <double>> posterior;
  vector <string> output;
  for(int i=0;i<obs.size();i++){
    vector <double> temp;
    double maxval = FLT_MIN;
    int ind; 
    for(int st=0;st<states.size();st++){
      temp.pb(fwd[i][st]*bkw[obs.size()-i-1][st]/p_fwd);
      if(temp[st] > maxval){maxval = temp[st]; ind = st;}
      cout<<"Posterior for "<<states[st]<<" : "<<temp[st]<<endl;
    }
    posterior.pb(temp);
    output.pb(states[ind]);
  }

  //Finding max probability at every step and producing sequence of hidden states 
  cout<<"The most probable sequence of hidden states is : "<<endl;
  for(int i=0;i<output.size();i++){
    cout<<i+1<<". "<<output[i]<<endl;
  }

}
