package com.example.secondhand.controller;

import com.example.secondhand.beans.Good;
import com.example.secondhand.beans.User;
import com.example.secondhand.mapper.AdminMapper;
import com.example.secondhand.mapper.GoodMapper;
import com.example.secondhand.mapper.ImageMapper;
import com.example.secondhand.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@Controller
public class IndexController {
    @Autowired
    GoodMapper goodMapper;
    @Autowired
    ImageMapper imageMapper;
    @Autowired
    private UserMapper userMapper;
    @Autowired
    AdminMapper adminMapper;


    @RequestMapping("/login")
    public String login() {
        return "loginnew";
    }
    @RequestMapping("/regester")
    public String regester(){

        return "regester";
    }

    @PostMapping("/checkregester")
    public String checkregester(@RequestParam int adminid,@RequestParam String password){
        System.out.println(adminid);
        System.out.println(password);
        adminMapper.insertadm(Integer.toString(adminid),password);
        return "loginnew";
    }

    @PostMapping("/loginCheck")
    public String loginCheck(@RequestParam String id, @RequestParam String password) {
        System.out.println(id);
        if (userMapper.findUserById(id,password)!=null)
            return "redirect:/index";
        else
            return "error";
    }

    @RequestMapping("/index")
    public String index(Model model) {
        List<Good> goods = goodMapper.selectAllGood();
        model.addAttribute("goods", goods);
        return "index";
    }

    @RequestMapping("/deletgood")
    public String deletgood(String goodid){
        System.out.println(goodid);
        imageMapper.deletimage(goodid);
        goodMapper.deletGood(goodid);
        return "redirect:/index";
    }

    @RequestMapping("/index1")
    public String index1(Model model) {
        List<User> users= userMapper.selectall();
        model.addAttribute("users",users );
        return "index1";
    }

    @RequestMapping("/deletuser")
    public String deletuser(String userid){
        System.out.println(userid);
        userMapper.deletuser(userid);
        return "redirect:/index1";
    }
}
