using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.Reflection;

/*
 Further info of the structure and behavourism will be 
 explained in Horror project TDD
 */

/// <summary>
/// SQLLiteInterFace GUI which consists of multiple classes
/// </summary>
[ExecuteInEditMode]
public class SqliteWindow : EditorWindow
{
    DatabaseSelection window;
    //Dummy string for input
    string myString = "Hello";
    const int columnCount = 2;

    /// <summary>
    /// Method for window activation through menu
    /// </summary>
    [MenuItem("Tools/DatabaseWindow")]
    public static void ShowWindow()
    {
        GetWindow<SqliteWindow>("DatabaseExamble");
    }



    //generates the graphics for the window
    private void OnGUI()
    {

        GUILayout.Label("Label", EditorStyles.boldLabel);

        myString = EditorGUILayout.TextField("Database Name", myString);

        //option buttons
        if (GUILayout.Button("Create"))
        {
            SQLiteInterFace.CreateDataBase(myString);
        }

        if (GUILayout.Button("Load"))
        {
            //load all the [databases directory] databases
            string[] databases = SQLiteInterFace.LoadDirectory();

            if (databases != null)
            {
                if (window != null) return;
                window = GetWindow<DatabaseSelection>("DatabaseSelection");

                foreach (string s in databases)
                {
                    window.AddEntry(s);
                }
                window.Populate();
            }
        }

        if (GUILayout.Button("Close"))
        {
            Close();
        }
    }

    //event when window is closed
    private void OnDestroy()
    {
        SQLiteInterFace.Save();
        window = null;
    }

    private class DatabaseSelection : EditorWindow
    {
        int selgridInt;
        string[] selections;
        //Check for the window if it is open

        private List<string> nameList = new List<string>();

        /// <summary>
        /// Adds a entry to the list
        /// </summary>
        /// <param name="a"></param>
        public void AddEntry(string a)
        {
            nameList.Add(a);
        }

        public void Populate()
        {
            //begin forming the box layout
            selections = nameList.ToArray();

            //iterate through the list and remove unnnecessary filepath
            for (int i = 0; i < selections.Length; i++)
            {
                selections[i] = selections[i].Substring(SQLiteInterFace.datapath.Length + 1, selections[i].Length - SQLiteInterFace.datapath.Length - 1);
            }

        }

        private void OnGUI()
        {
            //Create a selection box 
            CreateSelectionBox();
        }

        /// <summary>
        /// Creates a selection box for all the created databases 
        /// </summary>
        private void CreateSelectionBox()
        {
            selgridInt = GUILayout.SelectionGrid(selgridInt, selections, columnCount);
            GUILayout.BeginVertical("box");
            //integer for the selection
            if (GUILayout.Button("Select"))
            {
                //Load the database with the datapath in b[index]
                SQLiteInterFace.LoadDatabase(nameList[selgridInt]);
                ModificationWindow window = GetWindow<ModificationWindow>("ModificationWindow");
                window.Init(selections[selgridInt]);
                //close window
                Close();
            }

            //end the box layout 
            GUILayout.EndVertical();
        }
    }

    /// <summary>
    /// GUI for the database modifications after the selection of database
    /// </summary>
    private class ModificationWindow : EditorWindow
    {
        string databaseName;
        string[,] temp;
        List<Variable?> variables = new List<Variable?>();
        private Datatypes type;
        /// <summary>
        /// Adds new variable to the list
        /// </summary>
        public void AddVariable()
        {
            Variable? temp = default(Variable);
            variables.Add(temp);
        }

        /// <summary>
        /// Initializes the window
        /// </summary>
        /// <param name="name"></param>
        public void Init(string name)
        {
            databaseName = name;
        }

        /// <summary>
        /// generates GUI for the window
        /// </summary>
        private void GUIGenerator()
        {
            GUILayout.Label(databaseName, EditorStyles.boldLabel);

            if (GUILayout.Button("+")) AddVariable();

            //Iterate through struct list
            for (int i = 0; i < variables.Count; i++)
            {
                GUILayout.BeginVertical("box"); //Creates individual boxes for variables
                FieldInfo[] ps = variables[i].GetType().GetFields(BindingFlags.Instance | BindingFlags.Public);

                //iterate through struct fields
                foreach (FieldInfo field in ps)
                {
                    //box the struct for safekeeping
                    object bTemp = variables[i];

                    //iterate through different possibilities
                    if (System.Type.GetTypeCode(field.FieldType) == System.TypeCode.String)
                    {
                        //editor GUI field
                        string s = (string)field.GetValue(variables[i]);
                        s = EditorGUILayout.TextField("Variable Name", s);

                        //set field value
                        if(s != null)
                        field.SetValue(bTemp, SQLmethods.SafeTypeConversion(field, s));

                        //unbox
                        variables[i] = (Variable)bTemp;
                    }

                    //Check if the field is enum
                    if (field.FieldType.IsEnum)
                    {
                        //create variable for dropdown box
                        Datatypes a = (Datatypes)field.GetValue(variables[i]);
                        a = (Datatypes)EditorGUILayout.EnumPopup("Variable Type", a);

                        //set field value
                        field.SetValue(bTemp, SQLmethods.SafeTypeConversion(field, a));

                        //unbox
                        variables[i] = (Variable)bTemp;
                    }
                }
                GUILayout.EndVertical();
            }
        }


        private void OnGUI()
        {
            GUIGenerator();
            if (GUILayout.Button("Create Table"))
            {
                SQLiteInterFace.CreateTable("Poop", variables);
            }
        }

        private void OnDestroy()
        {
            SQLiteInterFace.Save();
        }
    }
}

/// <summary>
/// Template structure for room
/// </summary>
public struct Variable
{
    public string name;
    public Datatypes id;
}
