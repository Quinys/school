///https://www.spoj.com/problems/SUBXOR/
#include <iostream>
using namespace std;
class trienode {
public:
    int left_count, right_count;
    trienode* left;
    trienode* right;
    trienode()
    {
        left_count = 0;
        right_count = 0;

        left = NULL;

        right = NULL;
    }
};
void insert(trienode* root, int element)
{
    for (int i = 31; i >= 0; i--) {
        int x = (element >> i) & 1;

        if (x) {
            root->right_count++;
            if (root->right == NULL)
                root->right = new trienode();
            root = root->right;
        }
        else {
            root->left_count++;
            if (root->left == NULL)
                root->left = new trienode();
            root = root->left;
        }
    }
}
int query(trienode* root, int element, int k)
{
    if (root == NULL)
        return 0;
    int res = 0;
    for (int i = 31; i >= 0; i--) {
        bool current_bit_of_k = (k >> i) & 1;
        bool current_bit_of_element = (element >> i) & 1;

        if (current_bit_of_k) {
            if (current_bit_of_element) {
                res += root->right_count;
                if (root->left == NULL)
                    return res;
                root = root->left;
            }

            else {
                res += root->left_count;
                if (root->right == NULL)
                    return res;
                root = root->right;
            }
        }

        else {
            if (current_bit_of_element) {
                if (root->right == NULL)
                    return res;
                root = root->right;
            }

            else {
                if (root->left == NULL)
                    return res;
                root = root->left;
            }
        }
    }
    return res;
}

int n, k;
int arr [100000];

int main()
{

    int t; cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }

        int temp, temp1, temp2 = 0;
        trienode* root = new trienode();
        insert(root, 0);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            temp = arr[i];
            temp1 = temp2 ^ temp;
            total += query(root, temp1, k);
            insert(root, temp1);
            temp2 = temp1;
        }

        cout << total << "\n";
    }

    return 0;
}
