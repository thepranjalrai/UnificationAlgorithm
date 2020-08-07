#include<iostream>
#include<string>

using namespace std;

class expr
{
    string name;
    bool predicate;   //1 for predicate, 0 for argument

    expr* contains;
    int contain_count;

    public:

    void express (string tree)//(string _name, int _predicate, int word_count=0)
    {
        cout << "Defining " << tree << endl;
        contain_count = 0;

        cout << "Enter expression identifier : ";
        cin >> name;
        
        cout<<"Is this a predicate? : ";
        cin >> predicate;

        if(predicate)
        {
            cout << "How many expressions does it contain? : ";
            int word_count;
            cin >> word_count;

            contains = new expr;

            for(int i=0; i<word_count; i++)
            {
                string pseudo_name = tree + name + char(i + 48) + "]>";
                contains[contain_count++].express(pseudo_name);
            }
        }
    }

    void bifurcate(int depth)
    {
        cout << name << "_" << contain_count << endl;
        depth++;

        for(int i=0; i<contain_count; i++)
        {
            for(int k=0; k<depth; k++)
                cout << "\t";
            
            contains[i].bifurcate(depth);
        }
    }
};

/*
void verify(string expr)
{
    int bracket_state = 0;
    
    for(char c : expr)
    {
        if(c == '(')
            bracket_state++;
        else if(c == ')')
            bracket_state--;
    }
}

int main()
{
    string input;
    string lhs, rhs;
    
    getline(cin, input);

    bool seperated = false;
    for(char c : input)
    {
        if(c == '=')
        {
            seperated = true;
            continue;
        }

        if(!seperated)  lhs += c;
        else            rhs += c;
    }

    cout << "_" << lhs << "_\n" << "_" << rhs << "_\n";
}
*/

int main()
{
    expr one;
    one.express("_");
    cout << "\n\n\n";

    one.bifurcate(0);
}