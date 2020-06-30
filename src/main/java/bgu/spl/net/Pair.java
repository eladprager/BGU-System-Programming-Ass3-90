package bgu.spl.net;

public class Pair<V,U> {
    private V first;
    private U second;

    public Pair(V first,U second){
        this.first=first;
        this.second=second;
    }

    public V first(){
        return this.first;
    }

    public U second(){
        return this.second;
    }

    public boolean equals(Pair<V,U> other){
        if (this.first.equals(other.first) && this.second.equals(other.second)){
            return true;
        }
        return false;
    }
}
