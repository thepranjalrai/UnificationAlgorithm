#include<iostream>
#include<string>
#include<stack>

using namespace std;
string substitutions = "";

class expr
{
public:
    string name;
    stack<expr> args;

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
/*
    void bifurcate(int depth)
    {
        cout << name << "_" << args.size() << endl;
        depth++;

        while(!args.empty())
        {
            for(int k=0; k<depth; k++)
                cout << "\t";
            
            args.top().bifurcate(depth);
            args.pop();
        }
    }
*/
};

string appearance(expr e, string rets = "")
{
    rets += e.name;
    if(!e.args.empty())
    {
        rets += "[ ";
        while(!e.args.empty())
        {
            rets += appearance(e.args.top());
            e.args.pop();

            if(!e.args.empty()) rets += ", ";
        }
        rets += " ]";
    }
    //else rets += "  ";

    return rets;
}

string unify(expr lhs, expr rhs)
{
    //Step. 1: If Ψ1 or Ψ2 is a variable or constant, then:
    if(lhs.args.size() == 0 || rhs.args.size() == 0)
    {
        //a: If they are identical return nil.
        if(lhs.name == rhs.name)
        {
            //cout << lhs.name << " " << rhs.name << endl;
            return "NIL";
        }
        //b: Else if Ψ1 is a variable,
        else if(isupper(lhs.name[0]))
        {
            // a. then if Ψ1 occurs in Ψ2, then return FAILURE
            // b. Else return { (Ψ2/ Ψ1)}.
            if(appearance(rhs).find(lhs.name) != std::string::npos)
            {
                cout << endl << appearance(rhs) << endl << lhs.name << endl;
                return "FAILURE Ψ1 occurs in Ψ2";
            }
            else
            {
                string rets = "{" + appearance(lhs) + "/" + appearance(rhs) + "}";
                return rets;
            }
        }
        //c) Else if Ψ2 is a variable, 
        else if(isupper(rhs.name[0]))
        {
            // a. If Ψ2 occurs in Ψ1 then return FAILURE,
            // b. Else return {( Ψ1/ Ψ2)}.
            if(appearance(lhs).find(rhs.name) != std::string::npos)
            {
                cout << endl << appearance(lhs) << endl << rhs.name << endl;
                cout << appearance(lhs).find(rhs.name) << endl;
                return "FAILURE Ψ2 occurs in Ψ1";
            }
            else
            {
                string rets = "{" + appearance(rhs) + "/" + appearance(lhs) + "}";
                return rets;
            }
        }
        else
        {
            cout << lhs.name << "|" << rhs.name << endl;
            return "FAILURE all constants";
        }
    }

    // Step.2: If the initial Predicate symbol in Ψ1 and Ψ2 are not same, then return FAILURE.
    if(lhs.name != rhs.name)
        return "FAILURE different predicates";

    // Step. 3: IF Ψ1 and Ψ2 have a different number of arguments, then return FAILURE.
    if(lhs.args.size() != rhs.args.size())
        return "FAILURE argument count mismatch";

    // Step. 4: Set Substitution set(SUBST) to NIL. 
    // Available as globas "string substitution = "";"

    // Step. 5: For i=1 to the number of elements in Ψ1. 
    while(!lhs.args.empty())
    {
    // 	a) Call Unify function with the ith element of Ψ1 and ith element of Ψ2,
    //     and put the result into S.
        string S = unify(lhs.args.top(), rhs.args.top());
        //cout << endl << lhs.args.top().name << "\t" << rhs.args.top().name;
        //cout << "\t" << S << endl;
        lhs.args.pop();
        rhs.args.pop();

    //	b) If S = failure then returns Failure    
        if(S.find("FAILURE") != std::string::npos)
        {
            //cout << "\nFails" << S;
            cout << S << endl;
            return S;
        }
    //	c) If S ≠ NIL then do,
        if(S != "NIL")
        {
            // a. Apply S to the remainder of both L1 and L2.
            {
                //cout << "Incomplete Code";
                //exit(0);
            }
            // b. SUBST= APPEND(S, SUBST).
            {
                substitutions = substitutions + S + "\n";
            }
        }
    }

    //  Step.6: Return SUBST. 
    return substitutions;
}

int main()
{
    /*
    expr lhs;
    lhs.express("LHS_");
    cout << endl << appearance(lhs) << "\n\n\n";

    expr rhs;
    rhs.express("RHS_");
    cout << endl << appearance(rhs) << "\n\n\n";

    cout << appearance(lhs) << endl << appearance(rhs) << endl;

    cout << unify(lhs, rhs) << endl << endl <<endl;
    */

   cout << "How many predicates would you define? : ";
   int predicate_count;
   cin >> predicate_count;

   expr predicates[predicate_count];

    cout << endl;
    for(int i=0; i<predicate_count; i++)
    {
        cout << "\nEnter predicate " << i << " :-\n";

        string pseudo_name = "";
        pseudo_name = pseudo_name + char(i+48) + "_";

        predicates[i].express(pseudo_name);
    }
    cout << endl << endl;

    cout << "Predicates are :-\n";
    for(int i=0; i<predicate_count; i++)
    {
        cout << i << " " << appearance(predicates[i]) << endl;
    }
    cout << endl << endl;

    for(int i=0; i<predicate_count; i++)
    {
        for(int j=0; j<predicate_count; j++)
        {
            if(i==j) continue;

            cout << "....\nUnifying";
            cout << "\n> " << appearance(predicates[i]);
            cout << "\n> " << appearance(predicates[j]);
            cout << endl;

            substitutions = "";
            cout << unify(predicates[i], predicates[j]);
            cout << "....\n\n";
        }
    }
}