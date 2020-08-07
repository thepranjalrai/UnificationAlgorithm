#include<iostream>
#include<string>
#include<stack>

using namespace std;

class expr
{
    string name;
    bool predicate;   //1 for predicate, 0 for argument

    stack<expr> args;

public:
    void express (string tree)
    {
        cout << "Defining " << tree << endl;

        cout << "Expression name : ";
        cin >> this->name;

        cout << "Nested expressions? : ";
        int arg_count;
        cin >> arg_count;

        for(int i=0; i<arg_count; i++)
        {
            string pseudo_name = tree + name + "_" + char(i + 48) + " >";

            expr temp;
            temp.express(pseudo_name);

            args.push(temp);
        }
    }

    void bifurcate(int depth)
    {
        cout << name << "_" << args.size() << endl;
        depth++;

        //for(int i=0; i<args.size(); i++)
        while(!args.empty())
        {
            for(int k=0; k<depth; k++)
                cout << "\t";
            
            args.top().bifurcate(depth);
            args.pop();
        }
    }
};

int main()
{
    expr one;
    one.express("_");
    cout << "\n\n\n";

    one.bifurcate(0);
}