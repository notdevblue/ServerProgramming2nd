using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class Parse : MonoBehaviour
{
    public UnityEvent<List<string>, List<string>> OnPacketParsed;


    public void ParsePacket(string _response)
    {
        List<string> parsedKeys = new List<string>();
        List<string> parsedValues = new List<string>();

        if (!_response.Contains('#'))
        {
            OnPacketParsed.Invoke(null, null);
            return;
        }

        string[] splited = _response.Split('#');
        string[] keys = splited[0].Split(',');
        string[] values = splited[1].Split('@');

        for (int i = 0; i < keys.Length; ++i)
        {
            parsedKeys.Add(keys[i]);
        }

        for (int i = 0; i < values.Length; ++i)
        {
            parsedValues.Add(values[i]);
        }

        OnPacketParsed.Invoke(parsedKeys, parsedValues);
    }
}