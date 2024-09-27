using System;
using UnityEngine;

public class Melt : MonoBehaviour
{
    public Shader meltShader;
    public bool beginMelt = false;
    // 消融消耗的时间
    public float meltTime = 1;

    [Range(0.01f, 0.2f)]
    // 消融边缘的宽度
    public float edgeWidth = 0.06f;
    // 消融阈值
    public Texture2D noiseTex;
    public Color colorFirst = Color.blue;
    public Color colorSecond = Color.blue;

    [SerializeField] private float m_ThresholdValue = 0;
    private Material meltMaterial;

    private void Start()
    {
        if(!meltShader){
            Debug.Log("Should Add Melt Shader!");
        }
        if(!noiseTex){
            Debug.Log("Should Add Noise Texture!");
        }
        meltMaterial = GetComponentInChildren<SpriteRenderer>().material;
        meltMaterial.shader = meltShader;
        UpdateMaterial();
    }

    private void Update()
    {
        if(beginMelt){
            float speed = 1 / meltTime;
            m_ThresholdValue += speed * Time.deltaTime;
            UpdateMaterial();
            beginMelt = m_ThresholdValue <= 1;
        }
    }

    public void Reset()
    {
        beginMelt = false;
        m_ThresholdValue = 0;
        UpdateMaterial();
    }

    private void UpdateMaterial()
    {
        meltMaterial.SetFloat("_ThresholdValue", m_ThresholdValue);
        meltMaterial.SetTexture("_NoiseTex", noiseTex);
        meltMaterial.SetColor("_Color_First", colorFirst);
        meltMaterial.SetColor("_Color_Second", colorSecond);
        meltMaterial.SetFloat("_ThresholdValue", m_ThresholdValue);
        meltMaterial.SetFloat("_Width", edgeWidth);
    }
}
