package bgu.spl.net.srv;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Users {



    private static List<User> allUsers = new LinkedList<>();

    public static List<User> getAllUsers() {
        return allUsers;
    }

    public static User getUserByName(String name){
        for (int i=0;i<Users.getAllUsers().size();i++){
            if(Users.getAllUsers().get(i).getUsername().equals(name)){
                return Users.getAllUsers().get(i);
            }
        }
        return null;
    }

    public static void addUser(User user) {
        Users.allUsers.add(user);
    }


    public static class User{
        private String username;
        private String password;
        private List<bgu.spl.net.srv.Book> userBooks;
        private List<String> genre;


        public User(String username, String password) {
            this.username = username;
            this.password = password;
            this.userBooks = new LinkedList<>();
            this.genre = new LinkedList<>();
        }

        public List<String> getGenreList() {
            return this.genre;
        }

        public List<Book> getBooks(){
            return this.userBooks;
        }

        public String getUsername(){
            return this.username;
        }

        public String getPassword(){
            return this.password;
        }

        public void addUserBook(bgu.spl.net.srv.Book newBook) {
            this.userBooks.add(newBook);
        }

        public void deleteUserBook(Book book){
            this.getBooks().remove(book);
        }

        public void addGenre(String genre) {
            this.genre.add(genre);
        }

//        public void returnBook(Book book){
//            Stack<User> tmpStack=book.getBookHistory();
//            User tmpUser=tmpStack.pop();
//            tmpUser.getBook(book);
//        }

        public void getBook(Book book){
//            if (!book.getOwner().getUsername().equals(this.username)){
                for (int i=0;i<Users.getAllUsers().size();i++){
                    if(Users.getAllUsers().get(i).getBooks().contains(book)){
                        this.addUserBook(book);
                        Users.getAllUsers().get(i).deleteUserBook(book);
                    }
//                }
            }
        }
    }
}
