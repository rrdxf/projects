package com.example.secondhand.controller;



import com.example.secondhand.beans.ShopCart;
import com.example.secondhand.beans.User;
import com.example.secondhand.mapper.ShopcartMapper;
import com.example.secondhand.mapper.UserMapper;

import net.minidev.json.JSONObject;
import org.apache.commons.io.FilenameUtils;
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.core.io.FileSystemResource;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserMapper userMapper;

    @Autowired
    private ShopcartMapper shopcartMapper;


    private final String prefixPath= "H:\\java\\intelidea\\secondhand\\src\\main\\resources\\icon\\";

    @RequestMapping("/register")
    public int Register(String Userid,String Userpassword,String Userphone){
        System.out.println(Userid);
        System.out.println(Userpassword);
        System.out.println(Userphone);
        if(Userid!=null||Userpassword!=null||Userphone!=null){
            User user1=userMapper.findifnullbyId(Userid);
            if (user1==null) {
                User user=new User();
                user.setUserid(Userid);
                user.setUserpassword(Userpassword);
                user.setUserphone(Userphone);

                String Shopcarid = Userid;
                userMapper.insertUser(user);

                return 1;
            }
        }else {
            return 0;
        }
        return 0;
    }

    @RequestMapping("/login")
    public User login(String Userid,String Userpassword){
        System.out.println("Userid:"+Userid);
        System.out.println("Userps:"+Userpassword);
        User user=null;
        user=userMapper.findUserById(Userid,Userpassword);
        System.out.println(user.toString());
        System.out.println(user.getHoldGood().toString());
        System.out.println("Userid:"+Userid+"   Userpassword:"+Userpassword);
        if (user!=null){
            return user;
        }else
            return null;
    }


    @RequestMapping("/hello")
    public String hello(){

        System.out.println('c'+'b');return "hello";
    }

    @Resource
    HttpServletRequest request;
    @RequestMapping("/uploadicon")
    @ResponseBody
    public JSONObject uploadImg(@RequestParam(value = "file",required = false) MultipartFile[] file,String userid) throws IOException {


        System.out.println("uoloadicon:");
        System.out.println("userid:"+userid);
              System.out.println(file.toString());

        User user=userMapper.findifnullbyId(userid);
        if (user!=null){//判断用户是否存在，如果存在，则可以修改头像
              JSONObject res=new JSONObject();
              JSONObject resUrl=new JSONObject();
              List<String> imageurls=new ArrayList<>();
              int i=0;
              for (MultipartFile files:file){
                  //String filename= "test_"+userid+"_"+i;
                  String filename= "icon_"+userid;
                  String ext = FilenameUtils.getExtension(files.getOriginalFilename());
                  String filenames = filename + "." + ext;
                  userMapper.updateIcon(filenames, userid);
                  String pathname = prefixPath + filenames;
                  files.transferTo(new File(pathname));
                  imageurls.add("/download/icon/"+filenames);
                  res.put("msg", "");
                  res.put("code", 0);
                  i=i+1;
              }
              resUrl.put("src", imageurls);
              res.put("data", resUrl);
            return res;
        }
        JSONObject res=null;
        return res;
    }


    /**
     *
     * public JSONObject uploadImg(@RequestParam(value = "file",required = false) MultipartFile[] file, String userid) throws IOException {
     *
     *         JSONObject res=new JSONObject();
     *         JSONObject resUrl=new JSONObject();
     *         List<String> imageurls=new ArrayList<>();
     *         for (MultipartFile files:file){
     *             String filename= "icon_"+userid;
     *             String ext = FilenameUtils.getExtension(files.getOriginalFilename());
     *             String filenames = filename + "." + ext;
     *
     *             String pathname = prefixPath + filenames;
     *             files.transferTo(new File(pathname));
     *             imageurls.add("\\icon\\"+filenames);
     *             res.put("msg", "");
     *             res.put("code", 0);
     *         }
     *         resUrl.put("src", imageurls);
     *         res.put("data", resUrl);
     *         return res;
     *     }
     */



    //下载对应路径为fileName的文件
    @PostMapping("/download")
    public ResponseEntity<FileSystemResource> download(String fileName){
        System.out.println(fileName);
        File file = new File(prefixPath+fileName.replace("/","\\"));
        if(file.exists()&&file.canRead()){
            System.out.println(ResponseEntity.ok()
                    .contentType(MediaType.IMAGE_JPEG)
                    .body(new FileSystemResource(file)).toString());
            return ResponseEntity.ok()
                    .contentType(MediaType.IMAGE_JPEG)
                    .body(new FileSystemResource(file));}
        return null;
    }


}
