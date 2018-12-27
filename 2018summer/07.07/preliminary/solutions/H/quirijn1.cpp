/******************************************************************************/
/* Problem: Selection                                                         */
/* Solution: Binary Search                                                    */
/* Time: O(n log n)                                                           */
/* Author Quirijn Bouts                                                       */
// @EXPECTED_RESULTS@: CORRECT
/******************************************************************************/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void Code(){
	int n,s,f,k; //candidates, selected, fav, #dpoints
	vector<int> fpoints,opoints,dpoints; //fav points, other points, distributeable points
	//input
	cin >> n >> s >> f;
	int tmp;
	for(int i=0;i<f;i++){
		cin >> tmp;
		fpoints.push_back(tmp);
	}
	for(int i=0;i<n-f;i++){
		cin >> tmp;
		opoints.push_back(tmp);
	}
	cin >> k;
	for(int i=0;i<k;i++){
		cin >> tmp;
		dpoints.push_back(tmp);
	}
	//sorting
	sort(fpoints.begin(),fpoints.end(),[](int i,int j){return i>j;}); //high to low
	sort(opoints.begin(),opoints.end(),[](int i,int j){return i>j;}); //high to low
	reverse(dpoints.begin(),dpoints.end());

	auto func=[&](int adv){ //can we advance adv favourites?
	
		//kevin: added the following if statement
		//if it holds, we essentially don't need to beat anyone, we just need to see whether there are adv favorites that can be selected
		if (s-adv >= (int)opoints.size()) {
		 return (min(f,s) >= adv);
		}
		
		int toBeat=opoints[s-adv]; //we need adv fav's with at least this much points
		//we need to distribute all points, this may influence the 'toBeat' threshold
		//distribute  points which will be assigned to people which we do not want to advance (more than s-t non-favourites)
		for(int i=0;i< k-f-(s-adv); i++){
			toBeat=max(toBeat,opoints[opoints.size()-1-i]+dpoints[dpoints.size()-(k-f-(s-adv))+i]);
		}
		//now see if we can get adv favourites selected
		for(int i=0;i<adv;i++){
			int total=fpoints[i]+(adv-i>k?0:dpoints[adv-1-i]);
			if(total<toBeat){return false;}
		}
		return true;
	};

	//binary search to find number of fav's we can advance
	int low, mid, high;
	low  = max(0,s-(n-f));
	high = min(f,s)+1;
	while (low < high) {
	  mid = low+(high-low)/2;
	  if (func(mid) == true)
	    low = mid+1;
	  else
	    high = mid;
	}
	//low is first value for which func(x) is false, we want last true, so we output low-1
	cout << low-1 << endl;

}

int main(){
	int runs;
	cin >> runs;
	while(runs--){
		Code();
	}
	return 0;
}


