package com.example.schoolsell.beans;


import java.util.List;

public class User {
    private  String userid;

    private String userpassword;

    private String username;

    private String userphone;

    private String useraddress;

    private int userprofit;



    private String usericon;
    private List<Good> holdGood;

    public User(String userid, String username,String usericon) {
        this.userid = userid;
        this.username = username;
        this.usericon=usericon;
    }

    public User(){};

    @Override
    public String toString() {
        return "User{" +
                "userid='" + userid + '\'' +
                ", userpassword='" + userpassword + '\'' +
                ", username='" + username + '\'' +
                ", userphone='" + userphone + '\'' +
                ", useraddress='" + useraddress + '\'' +
                ", userprofit=" + userprofit +
                ", usericon='" + usericon + '\'' +
                ", holdGood=" + holdGood +
                '}';
    }

    public void setUserid(String userid) {
        this.userid = userid;
    }

    public void setUserpassword(String userpassword) {
        this.userpassword = userpassword;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setUserphone(String userphone) {
        this.userphone = userphone;
    }

    public void setUseraddress(String useraddress) {
        this.useraddress = useraddress;
    }

    public void setUserprofit(int userprofit) {
        this.userprofit = userprofit;
    }

    public void setUsericon(String usericon) {
        this.usericon = usericon;
    }

    public void setHoldGood(List<Good> holdGood) {
        this.holdGood = holdGood;
    }

    public String getUserid() {
        return userid;
    }

    public String getUserpassword() {
        return userpassword;
    }

    public String getUsername() {
        return username;
    }

    public String getUserphone() {
        return userphone;
    }

    public String getUseraddress() {
        return useraddress;
    }

    public int getUserprofit() {
        return userprofit;
    }

    public String getUsericon() {
        return usericon;
    }

    public List<Good> getHoldGood() {
        return holdGood;
    }
}
