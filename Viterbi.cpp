#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

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
  //Getting the transition probabliities for the states
  cout<<"Enter transitin probabliities for : "<<endl;
  double trans_prob;
  for(int i=0;i<states.size();i++){
    for(int j=0;j<states.size();j++){
      cout<<states[i]<<"->"<<states[j]<<" : ";
      cin>>trans_prob;
      transition_probability[mp(states[i],states[j])] = trans_prob;
    }
  }
  cout<<endl;
  //Getting the Emmissin probabilities
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

  vector <map<pair<string,string>,double>> V;
  map <pair<string,string>,double> temp;
  V.pb(temp);
  
  for(int i=0;i<states.size();i++){
    V[0][mp(states[i],"probability")] = start_probability[states[i]]*emmission_probability[mp(states[i],obs[0])];
    V[0][mp(states[i],"prev")] = -1;
    //cout<<V[0][mp(states[i],"probability")]<<endl;
  }

  double max_tr_prob;
  string prev_st_selected;
  double max_prob;
  for(int t=1; t<obs.size();t++){
    //map <pair<string,string>,double> temp;
    V.pb(temp);
    for(int st=0;st<states.size();st++){
      max_tr_prob = V[t-1][mp(states[0],"probability")]*transition_probability[mp(states[0],states[st])];
      prev_st_selected = states[0];
      double tr_prob;
      for(int prev_state = 1; prev_state<states.size();prev_state++){
        tr_prob = V[t-1][mp(states[prev_state],"probability")]*transition_probability[mp(states[prev_state],states[st])];
        if(tr_prob > max_tr_prob){
          max_tr_prob = tr_prob;
          prev_st_selected = states[prev_state];
        }
      }

      max_prob = max_tr_prob*emmission_probability[mp(states[st],obs[t])];
      V[t][mp(states[st],"probability")] = max_prob;
      int k;
      for(k=0;k<states.size();k++){
        if(states[k]==prev_st_selected){break;}
      }
      V[t][mp(states[st],"prev")] = k;      
    }

  }

  for(int i=0;i<V.size();i++){
    for(int k=0;k<states.size();k++){
      //cout<<states[k]<<" : "<<V[i][mp(states[k],"probability")]<<"\t";
    }
    //cout<<endl;
  }

  max_prob = FLT_MIN;
  
  for(int i=0;i<states.size();i++){
    max_prob = max(max_prob,V[obs.size()-1][mp(states[i],"probability")]);
  }
  
  vector <string> opt;
  int previous = 0;
  
  for(int i=0;i<states.size();i++){
    if(max_prob == V[obs.size()-1][mp(states[i],"probability")]){
      opt.pb(states[i]);
      break;
    }
    previous++;
  }

  for(int i=obs.size()-1;i>0;i--){
    opt.pb(states[V[obs.size()-1][mp(states[previous],"prev")]]);
    previous=V[obs.size()-1][mp(states[previous],"prev")];
  }
  cout<<"The Hidden states are :"<<endl;
  for(int i = opt.size()-1;i>=0;i--){
    cout<<opt[i]<<"\t\t";
  }
  cout<<endl<<"with maximum probability of "<<max_prob<<endl;
}
