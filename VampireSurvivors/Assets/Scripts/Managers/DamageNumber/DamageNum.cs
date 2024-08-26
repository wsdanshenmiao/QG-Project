using UnityEngine;
using TMPro;
using System.Collections;

public class DamageNum : MonoBehaviour
{
    public float LifeTime;

    [SerializeField] private float m_FloatSpeed;

    private TMP_Text m_Tex;

    private void Awake()
    {
        m_Tex = GetComponent<TMP_Text>();
    }

    private void Update()
    {
        transform.position += Vector3.up * m_FloatSpeed * Time.deltaTime;
    }

    public IEnumerator AutoRelease()
    {
        yield return new WaitForSeconds(LifeTime);
        DamageNumPool.Instance.Release(this);
    }

    public void SetText(int damage)
    {
        m_Tex.text = damage.ToString();
    }
}
