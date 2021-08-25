package com.example.schoolsell.beans;

public class Shopcart {
    String shopcartid;

    String  user_id;
    String  good_id;

    public Shopcart(String user_id, String good_id) {
        this.user_id = user_id;
        this.good_id = good_id;
    }

    public void setTotalprice(String totalprice) {
        this.totalprice = totalprice;
    }

    public String getTotalprice() {
        return totalprice;
    }

    String totalprice;

    public void setShopcartid(String shopcartid) {
        this.shopcartid = shopcartid;
    }


    @Override
    public String toString() {
        return "Shopcart{" +
                "shopcartid='" + shopcartid + '\'' +
                ", user_id='" + user_id + '\'' +
                ", good_id='" + good_id + '\'' +
                '}';
    }

    public String getShopcartid() {
        return shopcartid;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public void setGood_id(String good_id) {
        this.good_id = good_id;
    }

    public String getUser_id() {
        return user_id;
    }

    public String getGood_id() {
        return good_id;
    }
}
