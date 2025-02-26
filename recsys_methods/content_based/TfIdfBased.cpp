/*
 * TfIdfBased.cpp
 *
 *  Created on: 23/10/2015
 *      Author: blpadmin
 */

#include "TfIdfBased.h"

TfIdfBased::TfIdfBased(Dataset &d):data(d) {
}

TfIdfBased::~TfIdfBased() {
	// TODO Auto-generated destructor stub
}

void TfIdfBased::predictTarget(double minTfIdf, int maxTarget){
	Similarity calcSim(data);
	unordered_map<int,unordered_map<int,double> >::iterator itrTargUser = data.targetData.begin();
	unordered_map<int,double>::iterator itrTargItem, itrWordItem;
	unordered_map<string,double>::iterator itrWordUser;
	double tfIdfAlvo, rating, numerator, denomUser, denomItem, auxValue;
	int count = 0;

	calcSim.featuresTfIdf();
	for(; itrTargUser != data.targetData.end(); ++itrTargUser){
		itrTargItem = data.targetData[itrTargUser->first].begin();
		for(; itrTargItem != data.targetData[itrTargUser->first].end(); ++itrTargItem){
			itrWordUser = data.userModel[itrTargUser->first].begin();
			tfIdfAlvo = 0;
			numerator = 0;
			denomUser = 0;
			denomItem = 0;
			for(; itrWordUser != data.userModel[itrTargUser->first].end(); ++itrWordUser){
				if(data.indexItem[itrWordUser->first].find(itrTargItem->first) != data.indexItem[itrWordUser->first].end()) {
					if(itrWordUser->second > minTfIdf){
						tfIdfAlvo = data.indexItem[itrWordUser->first][itrTargItem->first];
						numerator += itrWordUser->second * tfIdfAlvo;
						denomUser += itrWordUser->second * itrWordUser->second;
						denomItem += tfIdfAlvo * tfIdfAlvo;
					}
				}
			}
			if(numerator == 0 || denomUser == 0 || denomItem == 0) {
				if(data.avgByUser.find(itrTargUser->first) != data.avgByUser.end()){
					rating = data.avgByUser[itrTargUser->first];
				} else {
					rating = 0;
				}
			} else {
				rating = numerator / (sqrt(denomUser) * sqrt(denomItem));
				rating *= 10.0;
			}
			//cout << numerator << "/(" << denomUser << "*" << denomItem << ") = " << rating << endl;
			//getchar();
			auxValue = data.itemContent[itrTargItem->first].imbdRatings;
			if(auxValue != 0){
				if (rating == 0) {
					rating = auxValue;
				} else if(auxValue >= 9){
					rating += 2;
				} else if (auxValue >= 8){
					rating += 1.5;
				} else if (auxValue >= 7){
					rating += 0.8;
				} else if (auxValue >= 6){
					rating += 0.3;
				} else if (auxValue >= 5){
					rating += 0;
				} else if (auxValue >= 3){
					rating -= 2;
				} else if (auxValue >= 3){
					rating -= 2.5;
				} else if (auxValue >= 2){
					rating -= 3;
				} else {
					rating -= 3.5;
				}
			} else {
				if (rating == 0) {
					rating = 5;
				}
			}
			if(rating > 10) rating = 10;
			if(rating < 1) rating = 1;
			rating = rating;
			data.targetData[itrTargUser->first][itrTargItem->first] = rating;

			count++;
			if(count >= maxTarget and maxTarget > 0) break;
		}
	}
}
