#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <exception>
using namespace std;


#include <assert.h>
#include <vector>
#include <map>

#define LINE_LEN (200)
#define TOTAL_NUM (2)

typedef unsigned long u32_t;
typedef long s32_t;

//typedef vector<vector<u32_t> *> vectorpt_t;
typedef vector<string>::iterator iter_t;
typedef map<string,string> Attribute_t;
typedef Attribute_t::iterator AttributeIter_t;
typedef enum {eOpen=0, eClose} TagStatus_t;



class HrmlNode
{
public:
	HrmlNode(ifstream cin)
    {
		TagStatus_t status;
    	string line;
    	getline(cin,line);
    	status = ExtractTag(line, m_tag);

    	if (status == eOpen)
    	{
        	getline(cin,line);
    		tagmap[tag].SetStatus(eOpen);
    	}
    	else if (status == eClose)
    	{
    		tagmap[tag].SetStatus(status);
    	}

        ParseOpenTag(openTag);
        m_status = eOpen;
    }
    virtual ~HrmlNode()
    {
    }

    void SetStatus(TagStatus_t status)
    {
    	m_status = status;
    }

    void GetAttrVal(string attrName)
    {
        if (m_attr.find(attrName) == m_attr.end())
        {
        	cout<<"Not Found!"<<endl;
        }
        else
        {
        	cout<<m_attr[attrName]<<endl;
        }
    }

private:
    TagStatus_t ExtractTag(string line, string &tag)
    {
    	TagStatus_t bResult = eOpen;
    	if (line.compare(0,1,"<") == 0)
    	{
    		if (line.find("<tag") != string::npos || line.find(" tag") != string::npos)
    		{
    			bResult = eOpen;
    		}
    	    else if (line.find("/tag") != string::npos)
    	    {
    			bResult = eClose;
    	    }
    	    else
    	    {
    	        assert(0);
    	    }
    		size_t tagStart = line.find("tag");
    		size_t tagEnd = line.find(" ",tagStart+1)-1;
    		tag = line.substr(tagStart, tagEnd);
    		assert(tag.length()>0);
    	}
        else
        {
            assert(0);
        }

        return bResult;
    }
    void ParseOpenTag(string openTag)
    {
        size_t equfound;
        equfound = openTag.find("=");
        while(equfound != string::npos)
        {
            size_t lhsStart, lhsEnd,rhsStart, rhsEnd;
            string lhs,rhs;

            lhsEnd = openTag.find_last_not_of(" ",equfound-1);
            lhsStart = openTag.find_last_of(" ",lhsEnd)+1;
            assert(lhsStart >= 0); // cannot find lhs
            assert(lhsEnd >= 0); // cannot find lhs
            assert(lhsStart < lhsEnd); // cannot find lhs

            lhs = openTag.substr(lhsStart,lhsEnd);
            assert(lhs.length()>0);

            openTag = openTag.substr(equfound+1);

            rhsStart = openTag.find_first_not_of(" ",0);
            assert(strcmp (&openTag[rhsStart], &'"') == 0);
            rhsStart++;

            rhsEnd = openTag.find_first_of(" ",rhsStart)-1;
            assert(strcmp (&openTag[rhsEnd], &'"') == 0);
            rhsEnd--;
            assert(rhsEnd <= openTag.length());
            assert(rhsEnd <= openTag.length());
            assert(rhsStart < rhsEnd);

            rhs = openTag.substr(rhsStart,rhsEnd);
            assert(rhs.length()>0);

            openTag = openTag.substr(rhsEnd+1);

            //assert(m_attr.find(lhs) == m_attr.end());
            m_attr[lhs] = rhs;
            //attr.insert(pair<string,string>(lhs, rhs));
        }
    }

    list<HrmlNode *> next;
    TagStatus_t m_status;
    Attribute_t m_attr;
    string m_tag;
};

int main() {

    ifstream cin("input");

    int N, Q;
    string line;

    cin>>N>>Q;

    for (int i = 0; i < 2*N; i++)
    {

    }

    for (int i = 0; i < Q; i++)
    {
    	string qtag, qattr, tagGroup;
    	getline(cin,line);

    	size_t uTildePos, uDotPos;
    	uTildePos = line.find("~");
    	assert(uTildePos != string::npos);
    	qattr = line.substr(uTildePos);

    	tagGroup = line.substr(0,uTildePos-1);
    	uDotPos = tagGroup.find(".");
    	while (uDotPos != string::npos)
    	{
    		qtag = tagGroup.substr(0,uDotPos-1);
    		assert(tagmap.find(qtag) != tagmap.end());
        	tagmap[qtag].GetAttrVal(qattr);

    		tagGroup = tagGroup.substr(uDotPos+1);
        	uDotPos = tagGroup.find(".");

    	}
    }
}
