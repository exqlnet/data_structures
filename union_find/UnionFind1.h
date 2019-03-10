
class UnionFind1{
    private:
        int *id;
        int count;
    
    public:
        UnionFind1(int n){
            id = new int[n];
            count = n;
            for (int i = 0;i<n;i++){
                id[i] = i;
            }
        }

        ~UnionFind1(){
            delete id;
        }

        int find(int i){

            return id[i];
        }

        void unionElements(int a, int b){
            int aID = find(a), bID = find(b);
            for (int i = 0; i<count; i++){
                if(id[i] == aID){
                    id[i] = bID;
                }
            }
        }

};


