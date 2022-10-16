using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

public class Table : MonoBehaviour
{
    public List<TableButton> tableButtons = new List<TableButton>();

    public void SetTable(string tableData)
    {
        if (tableData == "NULL") return;

        string[] parsed = tableData.Split('-');
        for (int i = 0; i < parsed.Length; ++i)
        {
            tableButtons[i].Set(parsed[i]);
        }
    }


    public void Clear()
    {
        tableButtons.ForEach(x => {
            x.Set("NULL");
        });
    }


    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();

        tableButtons.ForEach(x => {
            sb.Append(x.inner);
            sb.Append("-");
        });

        sb.Remove(sb.Length - 1, 1);

        return sb.ToString();
    }
}
