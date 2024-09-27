Shader "VampireSurvivors/MeltWithSprite"
{
    Properties
    {
        _MainTex ("Sprite Texture", 2D) = "white" {}
        _Color ("Tint", Color) = (1,1,1,1)
        [MaterialToggle] PixelSnap ("Pixel snap", Float) = 0
        [HideInInspector] _RendererColor ("RendererColor", Color) = (1,1,1,1)
        [HideInInspector] _Flip ("Flip", Vector) = (1,1,1,1)
        [PerRendererData] _EnableExternalAlpha ("Enable External Alpha", Float) = 0

        _NoiseTex ("噪声纹理", 2D) = "white" {}
        _Color_First ("第一消融色", Color) = (1, 0, 0, 1)
        _Color_Second ("第二消融色", Color) = (1, 0, 0, 1)
        _Width ("消融边缘宽度", Range(0,1)) = 0
        _ThresholdValue ("消融阈值", Range(0,1)) = 0
    }

    SubShader
    {
        Tags
        {
            "Queue"="Transparent"
            "IgnoreProjector"="True"
            "RenderType"="Transparent"
            "PreviewType"="Plane"
            "CanUseSpriteAtlas"="True"
        }

        Cull Off
        Lighting Off
        ZWrite Off
        Blend One OneMinusSrcAlpha

        Pass
        {
        CGPROGRAM
            #pragma vertex SpriteVert
            #pragma fragment frag
            #pragma target 2.0
            #pragma multi_compile_instancing
            #pragma multi_compile_local _ PIXELSNAP_ON
            #pragma multi_compile _ ETC1_EXTERNAL_ALPHA
            #include "UnitySprites.cginc"
            #include "Util.hlsl"

            sampler2D _NoiseTex;
            float _ThresholdValue ;
            float _Width ;
            float4 _Color_First;
            float4 _Color_Second;

            fixed4 frag(v2f i) : SV_Target
            {
                //计算灰度值
                float lum = luminance(tex2D(_NoiseTex, i.texcoord));
                float gray = lum - _ThresholdValue;
                //剔除完全消融像素
                clip(gray);

                //计算点是否在过渡区域以及混合系数
                fixed t = 1 - smoothstep(0.0, _Width, gray);
                //根据混合系数计算消融颜色
                fixed3 dissolveColor = lerp(_Color_First, _Color_Second, t);
                dissolveColor = pow(dissolveColor, 5);

                fixed4 color = tex2D(_MainTex, i.texcoord) * i.color;
                // 最终颜色 = 原始颜色和消融色的插值
                color.rgb = lerp(color.rgb, dissolveColor, t * step(0.0001, _ThresholdValue));

                color.rgb *= color.a;

                return color;
            }
        ENDCG
        }
    }    
}