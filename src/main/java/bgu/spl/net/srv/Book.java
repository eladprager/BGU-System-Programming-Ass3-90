package bgu.spl.net.srv;

import java.util.Stack;

public class Book {
//    private boolean isAcquired;
    private String genre;
    private String bookName;
//    private Users.User owner;
    private Stack<Users.User> bookHistory;

    public Book(String bookName,String genre) {
//        this.isAcquired = false;
        this.bookHistory = new Stack<>();
        this.genre = genre;
        this.bookName = bookName;
    }

//    public boolean isAcquired() {
//        return isAcquired;
//    }

    public Stack<Users.User> getBookHistory(){
        return this.bookHistory;
    }

    public void addToBookHistory(Users.User user){
        this.bookHistory.push(user);
    }

    public String getGenre() {
        return genre;
    }

    public String getBookName() {
        return bookName;
    }

    public void returnBook(){
        Stack<Users.User> tmpStack=this.getBookHistory();
        Users.User tmpUser=tmpStack.pop();
        tmpUser.getBook(this);
    }

//    public void setOwner(Users.User owner){
//        this.owner=owner;
//    }
//
//    public Users.User getOwner(){
//        return this.owner;
//    }
}
