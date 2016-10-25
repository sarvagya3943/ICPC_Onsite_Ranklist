# -*- coding: utf-8 -*-
import sys
import requests 
from bs4 import BeautifulSoup 


def parse_stuff() :
	# change 'amrita' to 'chennai' , 'kolkata' , 'kharagpur' for getting other sites data
	url = 'https://www.codechef.com/download/ACMICPC16/ACMIND16/amrita.html' 
	r = requests.get(url) 
	soup = BeautifulSoup(r.text,"html.parser")
	# find all rows 
	tr_list = soup.find_all('tr')
	# remove headers from the list 
	tr_list = tr_list[1:]
	return tr_list 

# remove <td> tags from the row 
def get_name(s) :
	# s would be <td>.......</td>
	ss = str(s) # convert to a string object first 
	size = len(ss)  
	return ss[4:size-5] # obvious 

if __name__ == '__main__' :
	# 'data_siteName.in' 
	filename = 'data_amrita.in'
	file = open(filename,'wb')
	my_list = parse_stuff() 
	# my_list has all the entries 
	# need to separate ranks , names , college name 
	rank = 1 
	ranks = [] 
	teams = [] 
	colleges = []
	for row in my_list :
		cnt = 0 
		team_name = "" 
		college_name = "" 
		for elem in row :
			cnt = cnt + 1 
			if cnt == 6 : 
				team_name = get_name(elem)
			elif cnt == 8 :
				college_name = get_name(elem)
		ranks.append(rank)
		teams.append(team_name)
		colleges.append(college_name)
		rank = rank + 1 
	length = len(ranks)
	file.write(str(length) + '\n')
	for i in xrange(0,length) :
		file.write(str(ranks[i]) + '\n' )
		file.write(str(teams[i]) + '\n' )
		file.write(str(colleges[i]) + '\n' ) 
	