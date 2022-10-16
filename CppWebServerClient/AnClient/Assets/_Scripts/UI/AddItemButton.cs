using UnityEngine;
using UnityEngine.UI;

public class AddItemButton : MonoBehaviour
{
    public new InputField name;
    public InputField createrName;
    public InputField explanation;


    private Button _button;
    private Table _table;



    private void Start()
    {
        _button = GetComponent<Button>();
        _table = FindObjectOfType<Table>();

        _button.onClick.AddListener(() => {
            Request.Instance.InsertItem(name.text, createrName.text, explanation.text, _table.ToString());

            _table.Clear();
            name.text = "";
            createrName.text = "";
            explanation.text = "";
        });
    }
}