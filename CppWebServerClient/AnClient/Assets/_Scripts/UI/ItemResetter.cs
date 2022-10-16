using UnityEngine;
using System.Collections.Generic;

public class ItemResetter : MonoBehaviour
{
    public GameObject prefab;

    public void Reset(List<string> key, List<string> data)
    {
        if (!Request.Instance.lastReq.Contains("get")) return;

        // ID, name, exp, creater, table

        for (int i = transform.childCount - 1; i >= 0; --i)
        {
            Destroy(transform.GetChild(i).gameObject);
        }


        data.ForEach(x =>
        {
            string[] datas = x.Split(',');
            Instantiate(prefab, this.transform)
                .GetComponent<Item>()
                .Init(datas[1], datas[2], datas[3], datas[0], datas[4]);


        });
    }
}