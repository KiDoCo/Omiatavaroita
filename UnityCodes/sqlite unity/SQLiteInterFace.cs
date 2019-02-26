using System;
using System.IO;
using System.Collections.Generic;
using System.Reflection;
using UnityEngine;
using Mono.Data.Sqlite;

public enum Datatypes
{
    NULL, INTEGER, REAL, TEXT, BLOB
}

public static class SQLiteInterFace
{
    static public string sourcePath = Path.GetFullPath(Path.Combine(Application.dataPath, @"..\"));
    static public string datapath = Path.Combine(sourcePath, @"Databases");
    static public string fileEnd = ".db";

    private static SqliteConnection conn;


    /// <summary>
    /// Creates the database into the datapath folder with a fileEnd
    /// </summary>
    /// <param name="name"></param>
    public static void CreateDataBase(string name)
    {
        //Add fileEnd to the name
        name += fileEnd;
        //Check if directory is present
        if (!Directory.Exists(datapath))
        {
            Directory.CreateDirectory(datapath);
            Debug.Log("Creating directory");
        }

        //Check if same named database exists
        if (!File.Exists(Path.Combine(datapath, name)))
        {
            Debug.Log("Creating");
            try
            {
                //create a database file
                SqliteConnection.CreateFile("test" + fileEnd);
                string file = Directory.GetFiles(sourcePath, "*" + fileEnd)[0];
                //copy the file to the datapath
                File.Copy(file, Path.Combine(datapath, name), false);
                //delete the original
                File.Delete(Path.Combine(sourcePath, "test" + fileEnd));

            }
            catch (Exception e)
            {
                Debug.LogError("Error while creating database" + e.Message);
            }

        }
        else
        {
            Debug.LogWarning("Database Exists");
        }
    }

    /// <summary>
    /// searches the datapath directory and loads all fileEnd files
    /// </summary>
    /// <returns></returns>
    public static string[] LoadDirectory()
    {
        //find files
        string[] files = Directory.GetFiles(datapath, "*" + fileEnd);
        Debug.Log(files.Length);

        if (files.Length <= 0)
        {
            Debug.LogError("Directory loading failed");
            return null;
        }

        return files;
    }

    public static void LoadDatabase(string name)
    {
        //check if database exist
        if (name == null)
        {
            Debug.LogError("Database doesn't exist");
            return;
        }

        try
        {
            //establish a connection to database
            conn = new SqliteConnection("data source =" + name);
            Debug.Log(conn);
            conn.Open();
            string sle = "Select * From " + name;

            using (SqliteCommand cmd = new SqliteCommand(sle, conn))
            {
                using (SqliteDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        Debug.Log(reader["test"].ToString());
                    }
                }
            }

        }

        catch (Exception e)
        {
            Debug.LogError("Error while loading database " + e.Message);
        }
    }
    /// <summary>
    /// Creates the table to connected database 
    /// </summary>
    /// <param name="name"></param>
    /// <param name="variables"></param>
    public static void CreateTable(string name, List<Variable?> infos)
    {
        try
        {
            string sql = "create table " + name + "(";
            for (int i = 0; i < infos.Count; i++)
            {
                FieldInfo[] info = infos[i].GetType().GetFields(BindingFlags.Public | BindingFlags.Instance);
                foreach (FieldInfo field in info)
                {
                    Debug.Log(field.Name);
                    if (Type.GetTypeCode(field.FieldType) == TypeCode.String)
                    {
                        Debug.Log("is string");
                        sql += (string)field.GetValue(infos[i]) + " ";
                    }

                    if (field.FieldType.IsEnum)
                    {
                        Debug.Log("is datattype");
                        Datatypes a = (Datatypes)field.GetValue(infos[i]);
                        sql += a.ToString();
                    }
                }

                if (infos.Count == i)
                    sql += ",";
            }

            sql += ");";
            Debug.Log(sql);
            //send command for database
            SqliteCommand command = new SqliteCommand(sql, conn);
            command.ExecuteNonQuery();
            Debug.Log("Created table");

        }
        catch (Exception e)
        {
            Debug.LogError("Table creation fails " + "\n" + "Error message :" + e.Message);
        }
    }

    public static void Save()
    {
        conn.Close();
    }
}

