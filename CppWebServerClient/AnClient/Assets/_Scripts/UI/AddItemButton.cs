using UnityEngine;
using UnityEngine.UI;

public class AddItemButton : MonoBehaviour
{
    public new InputField name;
    public InputField createrName;
    public InputField explanation;


    private Button _button;



    private void Start()
    {
        _button = GetComponent<Button>();

        _button.onClick.AddListener(() => {
            Request.Instance.InsertItem(name.text, createrName.text, explanation.text);
        });
    }
}