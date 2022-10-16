using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Networking;

public class Request : MonoBehaviour
{
    public UnityEvent<string> OnReqArrived;
    public string m_server_addr = "localhost";
    public ushort m_server_port = 36000;

    public void Req()
    {

    }

    public void GetItem(string _name)
    {
        if (!CheckRegex(_name))
        {
            Debug.Log("Regex fail");
        }

        StartCoroutine(SendRequest("/get/item/", ("name", _name)));
    }

    public void GetAllItem()
    {
        StartCoroutine(SendRequest("/get/allitem/", ("", "")));
    }

    public void InsertItem(string _name, string _creatername, string _explanation, string _tabledata = "NULL")
    {
        if (!CheckRegex(_name) ||
            !CheckRegex(_creatername) ||
            !CheckRegex(_explanation) ||
            !CheckRegex(_tabledata)) // TODO: 서버로 INSERT 해야 함
        {
            Debug.LogError("Regex fail");
            return;
        }

        StartCoroutine(SendRequest("/set/item/",
                                   ("name", _name),
                                   ("creatername", _creatername),
                                   ("explanation", _explanation),
                                   ("tabledata", _tabledata)));
    }

    IEnumerator SendRequest(string _path, params (string, string)[] _querystring)
    {
        string query = $"{m_server_addr}:{m_server_port}{_path}{QuerystringBuilder(_querystring)}";

        UnityWebRequest req
            = UnityWebRequest.Get(query);

        yield return req.SendWebRequest();

        switch (req.result)
        {
            case UnityWebRequest.Result.Success:
                OnReqArrived.Invoke(req.downloadHandler.text);
                Debug.Log(req.downloadHandler.text);
                break;

            default:
                Debug.LogError(req.downloadHandler.text);
                break;
        }
    }


    private string QuerystringBuilder(params (string, string)[] _params)
    {
        StringBuilder sb = new StringBuilder();
        if (_params[0].Item1 == "") return "";

        sb.Append("?");

        for (int i = 0; i < _params.Length; ++i)
        {
            sb.Append(_params[i].Item1);
            sb.Append("=");
            sb.Append(_params[i].Item2);
            sb.Append("&");
        }
        sb.Remove(sb.Length - 1, 1);


        return sb.ToString();
    }


    private bool CheckRegex(string str)
    {
        Regex rx = new Regex(@"[a-z|A-Z]");
        return rx.Match(str).Success;
    }
}
