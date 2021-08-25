package com.example.secondhand.controller;


import com.example.secondhand.beans.Good;
import com.example.secondhand.beans.Image;
import com.example.secondhand.beans.User;
import com.example.secondhand.mapper.GoodMapper;
import com.example.secondhand.mapper.ImageMapper;
import net.minidev.json.JSONObject;
import org.apache.commons.io.FilenameUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

@RestController
@RequestMapping("/good")
public class GoodController {

    private final String prefixPath= "H:\\java\\intelidea\\secondhand\\src\\main\\resources\\icon\\";
    @Autowired
    GoodMapper goodMapper;
    @Autowired
    ImageMapper imageMapper;

    @RequestMapping("/findgood")
    public Good findgood(String Goodid){
        if (Goodid!=null)
            return goodMapper.selectGoodbyid(Goodid);
        else
            return null;
    }
    @RequestMapping("/insertgood")
    public int addgood(String Goodid,
                       String Goodname,
                       String Goodprice,
                       String Goodexpression,
                       String Userid){
        if (Goodid!=null||Goodname!=null||Goodprice!=null||Goodexpression!=null||Userid!=null){
            Good good=new Good();
            good.setGoodid(Goodid);
            good.setGoodname(Goodname);
            good.setGoodprice(Goodprice);
            good.setGoodexpression(Goodexpression);
            good.setOwnerid(Userid);
            goodMapper.insertGood(good);
            return 1;
        }else
            return 0;
    }


    @RequestMapping("/allgood")
    private List<Good> findallgood(){
        List<Good> goods=new ArrayList<>();
        goods=goodMapper.selectAllGood();
        System.out.println(goods.size());
        //System.out.println(goods);
        return goods;
    }
    @RequestMapping("/finduserandgood")
    public List<Good> selectgoodanduser(String userid){
        List<Good> list=new ArrayList<>();
        list=goodMapper.selectGoodbyuserid(userid);
        return list;
    }


    @Resource//物品照片的上传
    HttpServletRequest request;
    @RequestMapping("/uploadgoodimg")
    @ResponseBody
    public HashMap<String ,Object> uploadImg(@RequestParam(value = "file",required = false) MultipartFile[] file,
                                    String userid,
                                    String goodname,
                                    String goodprice,
                                    String goodexpression) throws IOException {



        JSONObject res=new JSONObject();
        JSONObject resUrl=new JSONObject();

        //存储图片名的list
        List<String> imageurls=new ArrayList<>();

        List<Image> images1=new ArrayList<>();
        List<String> imagelist=new ArrayList<>();
        int i=0;
        //List<Good>goods=goodMapper.selectAllGood();
        String goodid=Integer.toString((int)(Math.random()*(1000-1)+1));
        goodMapper.insertGood(new Good(goodid,goodname,goodprice,goodexpression,userid));
        for (MultipartFile files:file){
            //String filename= "test_"+userid+"_"+i;
            String filename= "icon_"+userid+"good_"+goodid+"_"+i;
            String ext = FilenameUtils.getExtension(files.getOriginalFilename());
            String filenames = filename + "." + ext;
            imageurls.add(filenames);
            imagelist.add(filenames);
            images1.add(new Image(filenames,goodid));
            String pathname = prefixPath + filenames;
            files.transferTo(new File(pathname));
            //imageurls.add("/download/icon/"+filenames);
            res.put("msg", "");
            res.put("code", 0);
            i=i+1;
        }

        List<Image> images=imageMapper.findImage();
        System.out.println(imagelist);
        for (int j=0, m=images.size();j<imagelist.size();j++,m++){

            imageMapper.inSertImage(new Image(Integer.toString((int)(Math.random()*(1000-1)+1)),imagelist.get(j),goodid));
        }

        System.out.println(imagelist.toString());
        HashMap<String,Object> map=new HashMap<>();
        map.put("goodid",goodid);
        map.put("imagelist",images1);
        return map;
    }

    @RequestMapping("/deletgood")
    public int deletgood(String goodid){
        imageMapper.deletimage(goodid);
        goodMapper.deletGood(goodid);
        return 0;
    }

}
