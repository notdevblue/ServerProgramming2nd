using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Table : MonoBehaviour
{
    public List<TableButton> tableButtons = new List<TableButton>();

    public void Reset(List<string> keys, List<string> datas)
    {
        datas.ForEach(x => {
            string[] tableData = x.Split(',')[4].Split('*');
            for (int i = 0; i < tableData.Length; ++i)
            {
                tableButtons[i].Set(tableData[i]);
            }
        });
    }
}
