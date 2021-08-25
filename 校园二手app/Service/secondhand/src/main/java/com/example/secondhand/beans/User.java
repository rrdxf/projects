package com.example.secondhand.beans;

import org.springframework.context.annotation.Bean;

import java.util.List;


public class User {

    private  String Userid;

    private String Userpassword;

    private String Username;

    private String Userphone;

    private String Useraddress;

    private int Userprofit;



    private String Usericon;
    private List<Good> HoldGood;

    public List<Good> getHoldGood() {
        return HoldGood;
    }
    public String getUsericon() {
        return Usericon;
    }

    public void setUsericon(String usericon) {
        Usericon = usericon;
    }
    public void setHoldGood(List<Good> holdGood) {
        HoldGood = holdGood;
    }

    @Override
    public String toString() {
        return "User{" +
                "Userid='" + Userid + '\'' +
                ", Userpassword='" + Userpassword + '\'' +
                ", Username='" + Username + '\'' +
                ", Userphone='" + Userphone + '\'' +
                ", Useraddress='" + Useraddress + '\'' +
                ", Userprofit=" + Userprofit +
                ", Usericon='" + Usericon + '\'' +
                ", HoldGood=" + HoldGood.toString() +
                '}';
    }

    public void setUserid(String userid) {
        Userid = userid;
    }

    public void setUserpassword(String userpassword) {
        Userpassword = userpassword;
    }

    public void setUsername(String username) {
        Username = username;
    }

    public void setUserphone(String userphone) {
        Userphone = userphone;
    }

    public void setUseraddress(String useraddress) {
        Useraddress = useraddress;
    }

    public void setUserprofit(int userprofit) {
        Userprofit = userprofit;
    }

    public void setPictureaddress(String pictureaddress) {
        Usericon = pictureaddress;
    }

    public String getUserid() {
        return Userid;
    }

    public String getUserpassword() {
        return Userpassword;
    }

    public String getUsername() {
        return Username;
    }

    public String getUserphone() {
        return Userphone;
    }

    public String getUseraddress() {
        return Useraddress;
    }

    public int getUserprofit() {
        return Userprofit;
    }

    public String getPictureaddress() {
        return Usericon;
    }

}
