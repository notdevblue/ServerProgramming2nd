using UnityEngine;
using UnityEngine.UI;

public class SearchItemButton : MonoBehaviour
{
    public new InputField name;
    private Button _button;

    private void Start()
    {
        _button = GetComponent<Button>();

        _button.onClick.AddListener(() => {
            Request.Instance.GetItem(name.text);
        });
    }
}