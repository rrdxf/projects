package com.example.schoolsell.connect;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class FileUtil {

    public static String externalFilesDir;

    /**
     * 检查文件是否存在
     * @param fileName 要检查的文件名
     * @return boolean 表示文件是否存在
     */
    public static boolean isFileExist(String fileName){
        File file = new File(fileName);
        return file.exists();
    }

    /**
     *
     * @param file 目标路径对应File对象
     * @return 若目录存在则返回true,否则尝试创建目录并返回结果
     */
    public static boolean makeDir(File file) {
        if(!file.exists())
            return file.mkdirs();
        return true;
    }

    /**
     *创建文件
     * @param fileName 要创建的File对象对应的文件名
     * @return fileName对应的File对象
     */
    public static File createFile(String fileName) throws IOException {
        File file = new File(fileName);
        boolean isCreated = file.createNewFile();
        return isCreated?file:null;
    }

    /**
     * 将输入流写入到文件中
     * @param fileName 目标文件对应路径
     * @param in    输入流
     * @throws IOException
     */
    public static void writeStream2File(String fileName, InputStream in) throws IOException {
        //new一个文件对象用来保存图片，默认保存当前工程根目录
        File file = new File(fileName);
        if(file.exists()) file.delete();
        file.createNewFile();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        //创建一个Buffer字符串
        byte[] buffer = new byte[1024];
        //每次读取的字符串长度，如果为-1，代表全部读取完毕
        int len = 0;
        //使用一个输入流从buffer里把数据读取出来
        while( (len=in.read(buffer)) != -1 )
            out.write(buffer, 0, len);
        //得到图片的二进制数据，以二进制封装得到数据，具有通用性
        byte[] data = out.toByteArray();
        //创建输出流
        FileOutputStream fos = new FileOutputStream(file);
        //写入数据
        fos.write(data);
        fos.flush();//清空输出流
        fos.close();//关闭输出流
    }

}
