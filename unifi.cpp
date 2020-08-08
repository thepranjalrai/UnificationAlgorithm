#include<iostream>
#include<string>
#include<stack>

using namespace std;

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
};

string appearance(expr e, string rets = "")
{
    //string rets = "";
    rets += e.name;
    //cout << e.name;
    if(!e.args.empty())
    {
        rets += "[ ";
        //cout << "[ ";
        while(!e.args.empty())
        {
            appearance(e.args.top(), rets);
            e.args.pop();
        }
        rets += " ] ";
        //cout << " ] ";
    }
    else if(e.args.size() > 1) cout << "  ";

    return rets;
}

string unify(expr lhs, expr rhs)
{
//Step 1 :  
//a: If they are identical lreturn nil.
    if(appearance(lhs) == appearance(rhs))
    {
        return "NIL";
    }
//b: Else if Ψ1is a variable, 
//		a. then if Ψ1 occurs in Ψ2, then return FAILURE
//		b. Else return { (Ψ2/ Ψ1)}.
    if(appearance(rhs).find(appearance(lhs)))
    {
        return "FAILURE";
    }
    else
    {
        cout << endl << endl;
        cout << "{ (";
        cout << appearance(lhs);
        cout << "/";
        cout << appearance(rhs);
        cout << ")}.";
        cout << endl << endl;
    }
//c) Else if Ψ2 is a variable, 
//		a. If Ψ2 occurs in Ψ1 then return FAILURE,
//		b. Else return {( Ψ1/ Ψ2)}.
    if(appearance(lhs).find(appearance(rhs)))
    {
        return "FALSE";
    }
    else
    {
        cout << endl << endl;
        cout << "{ (";
        cout << appearance(rhs);
        cout << "/";
        cout << appearance(lhs);
        cout << ")}.";
        cout << endl << endl;
    }
// Step.2: If the initial Predicate symbol in Ψ1 and Ψ2 are not same, then return FAILURE.
    if(lhs.name != rhs.name)
        return "FAILURE";
// Step. 3: IF Ψ1 and Ψ2 have a different number of arguments, then return FAILURE.
    if(lhs.args.size() != rhs.args.size())
        return "FAILURE";
// Step. 4: Set Substitution set(SUBST) to NIL. 
    string substitutions = "";
// Step. 5: For i=1 to the number of elements in Ψ1. 
    while(!lhs.args.empty())
    {
// 	a) Call Unify function with the ith element of Ψ1 and ith element of Ψ2,
//     and put the result into S.
        string S = unify(lhs.args.top(), rhs.args.top());
        lhs.args.pop();
        rhs.args.pop();
//	b) If S = failure then returns Failure    
        if(S == "FAILURE") return "FAILURE";
//	c) If S ≠ NIL then do,
        if(S != "NIL")
//  	a. Apply S to the remainder of both L1 and L2.
        {
            cout << "Incomplete Code";
            exit(0);
        }
//		b. SUBST= APPEND(S, SUBST).
        {
            substitutions = substitutions + ", " + S;
        }
    }
//  Step.6: Return SUBST. 
    return substitutions;
}

int main()
{
    expr lhs;
    lhs.express("L_");
    cout << "\n\n\n";

    expr rhs;
    rhs.express("R_");
    cout << "\n\n\n";

    unify(lhs, rhs);
/*
    lhs.bifurcate(0);
    cout << "\n\n\n";

    rhs.bifurcate(0);
    cout << "\n\n\n";
*/
}