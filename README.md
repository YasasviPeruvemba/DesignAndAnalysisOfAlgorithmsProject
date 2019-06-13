# DesignAndAnalysisOfAlgorithmsProject
The course project for CS204 i.e Design and Analysis of Algorithms

## Introduction

To understand, implement and analyze the algorithms used to effectively solve
Hidden Markov Models. Hidden Markov Model (HMM) is a statistical Markov
model in which the system being modeled is assumed to be a Markov process with
unobserved (i.e. hidden) states.
## Hidden Markov Models
Hidden Markov models are especially known for their application in reinforcement
learning and temporal pattern recognition such as speech, handwriting, gesture
recognition, part-of-speech tagging, musical score following, partial discharges and
bioinformatics.
## Algorithm Analysis
### Viterbi Algorithm
The Viterbi algorithm is a dynamic programming algorithm for finding the most likely
sequence of hidden states, called the Viterbi path that results in a sequence 
of observed events.    
**Complexity Analysis** :   
The Time complexity of this algorithm is
**O(NT<sup>2</sup>)**
And the space complexity is
**O(T<sup>2</sup> + kT + NT)**  
**K** is the total number of unique observable states.  
**T** is the total number of unique hidden states.   
**N** is the length of the observed sequence.   
### Forward-Backward Algorithm
The forward–backward algorithm is an
algorithm for hidden Markov models which computes the posterior
marginal probabilities of all hidden state variables for a set of observed sequence
of events.     
**Complexity Analysis** :   
The Total Time Complexity such that each **z** is considered is **O(nm<sup>2</sup>)**  
z ∈Hidden States in a layer   
m is the set of Hidden States   
n is the length of observed sequence   
 
### CarpeDiem Algorithm
In order to determine the end point of the best path
to a given layer, one can avoid inspecting all vertices in that layer. In particular,
after sorting the vertices in a layer according to their vertical weight, the search
can be stopped when the difference in vertical weight of the best node so far and
the next vertex in the ordering is big enough to counterbalance any advantage that
can be possibly derived from exploiting a better transition from a better ancestor.   
**Complexity Analysis** :  
The best case happens when horizontal rewards, being equal for each
transition, do not provide any discriminative power. In such a case the
right hand side of the inequality is zero and the
inequality is guaranteed to be satisfied immediately. Moreover, being
the backward strategy based on a bound similar to the one that leads
to Formula mentioned in the Report, it will never open any other vertex.
Then, a single vertex per layer is opened and CarpeDiem has order of
**O(T + TKlog(K)) = O(TKlog(K))**
time complexity.
A more formal argument about CarpeDiem complexity is stated by
CarpeDiem has **O(TK<sup>2</sup> )** worst case time complexity and
**O(TKlog(K))** best case time complexity.

## Conclusion
This project has been instrumental in understanding Hidden Markov Models and
their immense contributions towards the advancements in technologies like Speech
Synthesis, Speech tagging, Bioinformatics and Cryptanalysis to name a few. We
have also analysed different approaches to solve these class of Hidden Markov
Model problems via various algorithms and finally a slightly optimised algorithm.  
The Viterbi algorithm uses a dynamic programming approach to determine the
hidden state sequence from a given set of observed sequence.  
The Forward-Backward Algorithm also uses a dynamic approach, but to calculate
the state probabilities, for further operations.  
The CarpeDiem algorithm is an optimization on the Viterbi algorithm which works
on a dynamic approach, but eliminating a few corner case calculation making it
significantly more efficient than the pre-existing Viterbi algorithm.
Hence, we have analysed these three algorithms as the most prominent way to
solve Hidden Markov Models.
