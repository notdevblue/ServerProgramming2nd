using UnityEngine;
using UnityEngine.UI;

public class Item : MonoBehaviour
{
    public Text itemName;
    public Text explanation;
    public Text createrName;
    public string id;
    public string tabledata;

    public Button btnSelf;
    public Button btnRecipe;

    Table _table;

    public void Init(string itemName, string explanation, string createrName, string id, string tabledata)
    {
        this.itemName.text = itemName;
        this.explanation.text = explanation;
        this.createrName.text = createrName;
        this.id = id;
        this.tabledata = tabledata;
    }


    private void Start()
    {
        _table = FindObjectOfType<Table>();

        btnSelf.onClick.AddListener(() => {
            Request.Instance.curclickeditemname = itemName.text;
        });

        btnRecipe.onClick.AddListener(() => {
            _table.SetTable(tabledata);
        });
    }
}