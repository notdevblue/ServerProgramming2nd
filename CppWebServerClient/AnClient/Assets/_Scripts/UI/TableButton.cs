using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TableButton : MonoBehaviour
{
    public Text text;
    public string inner;

    public void Set(string name)
    {
        inner = name;
        
        if (name == "NULL")
        {
            text.text = "";
        }
        else
        {
            text.text = name;
        }
    }

    private void Start()
    {
        GetComponent<Button>().onClick.AddListener(() => {
            if (Request.Instance.curclickeditemname != "")
            {
                Set(Request.Instance.curclickeditemname);
                Request.Instance.curclickeditemname = ""; // TODO: 아이템 클릭 시 저장되고 테이블 클릭하면 그거 넣고, 이제 save 할 때 그 테이블 데이터 넘기게. 아이템 조합 버튼 누르면 테이블 바뀌어야 함. 테이블 초기화 넣어야 함
            }   
        });
    }
}
