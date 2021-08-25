package com.example.secondhand.beans;

import java.util.List;

public class ShopCart {
    String shopcartid;

    String  user_id;
    String  good_id;

    public void setShopcartid(String shopcartid) {
        this.shopcartid = shopcartid;
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
