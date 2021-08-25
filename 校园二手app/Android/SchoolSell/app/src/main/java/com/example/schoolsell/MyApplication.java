package com.example.schoolsell;

import android.app.Application;

import com.example.schoolsell.beans.Good;
import com.example.schoolsell.beans.Shopcart;
import com.example.schoolsell.beans.User;

import java.util.List;

public class MyApplication extends Application {


    private User user;

    private List<Good> goods;

    boolean islog;

    public String getGood_show_goodid() {
        return good_show_goodid;
    }

    public void setGood_show_goodid(String good_show_goodid) {
        this.good_show_goodid = good_show_goodid;
    }

    private String good_show_goodid;

    private List<Shopcart>shopcarts;

    public void setShopcarts(List<Shopcart> shopcarts) {
        this.shopcarts = shopcarts;
    }

    public List<Shopcart> getShopcarts() {
        return shopcarts;
    }

    @Override
    public String toString() {

        return user.toString();
    }



    public void setUser(User user) {
        this.user = user;
    }

    public User getUser() {
        return user;
    }
    public boolean isIslog() {
        return islog;
    }

    public void setIslog(boolean islog) {
        this.islog = islog;
    }
    public List<Good> getGoods() {
        return goods;
    }

    public void setGoods(List<Good> goods) {
        this.goods = goods;
    }
}
