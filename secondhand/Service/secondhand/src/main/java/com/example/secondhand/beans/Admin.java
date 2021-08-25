package com.example.secondhand.beans;

public class Admin {
    String adminid;
    String password;

    public void setAdminid(String adminid) {
        this.adminid = adminid;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getAdminid() {
        return adminid;
    }

    public String getPassword() {
        return password;
    }

    public Admin(String adminid, String password) {
        this.adminid = adminid;
        this.password = password;
    }
}
