
void main(void)
{
    float c = gl_Color.r * 0.21 + gl_Color.g * 0.71 + gl_Color.b * 0.07;
    
    gl_FragColor = vec4(c,c,c,gl_Color.a);  
}
