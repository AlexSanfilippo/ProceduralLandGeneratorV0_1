#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <headers/shader_s.h>

#include <iostream>

/*Add Matric Algebra Functions*/
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


//function headers
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    //tp 
    std::cout << "calling Shader constructor..." << std::endl;

    Shader ourShader("3.3.shader.vs", "3.3.shader.fs");
    
    //Shader ourShader("C:/Users/2015a/Documents/C++ Projects/OpenGLProjects/Include/headers/3.3.shader.vs",
    //    "C:/Users/2015a/Documents/C++ Projects/OpenGLProjects/Include/headers/3.3.shader.fs"); 
    
    // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.9f, -0.9f, 0.0f,  1.0f, 0.0f, 1.0f,  // bottom right
        -0.9f, -0.9f, 0.0f,  0.0f, 1.0f, 1.0f,  // bottom left
         0.0f,  0.9f, 0.0f,  0.0f, 0.0f, 0.0f   // top 
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1/*location*/, 3/*number of values*/, GL_FLOAT/*d_type*/, GL_FALSE, 6 * sizeof(float)/*size*/, (void*)(3 * sizeof(float))/*offset*/);
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    
    /*Tut: see max number of vertex attributes (aka inputs to the vertex shader) allowed on my hardware*/
    /*
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    */

    /*Transformations-basic vector transformation*/
    /*
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); //glm vector of 3 4 floats
    glm::mat4 trans = glm::mat4(1.0f); //id matrix
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); //(id matrix, transformation vector) = translation matrix
    vec = trans * vec; //multiply our vector by the translation matrix
    std::cout << vec.x << vec.y << vec.z << std::endl;
    */
    /*Rotate and Scale an object*/
    /*
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(1.0, 1.0, 1.0));
    */
    

    bool moveTriangle = false;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //rotate over time
        /*
        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::scale(trans, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime()))); //bouncy
        trans = glm::scale(trans, glm::vec3(2.0* glfwGetTime(), 2.0* glfwGetTime(), 2.0* glfwGetTime())); //zooming
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        //pass trans matrix to the vertex shader
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        */

        // update the uniform color -pulsing green
        /*
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        ourShader.setFloat4("uniColor", 0.0f, greenValue, 0.0f, 1.0f); //works
        */
        //pulsing vaporwave colors 
        float timeValue = glfwGetTime();
        float colorMod = (sin(timeValue) / 2.0f + 0.5f)/5.0f;
        ourShader.setFloat1("pulse", colorMod);

        //move triangle
        //float timeValue = glfwGetTime();
        if (moveTriangle) {
            float posModX = (sin(timeValue) / 2.0f + 0.5f) / 3.0f;
            float posModY = (cos(timeValue) / 2.0f + 0.5f) / 3.0f;
            ourShader.setFloat1("offsetX", posModX);
            ourShader.setFloat1("offsetY", posModY);
        }

        //fractal stuff
        ourShader.setFloat1("systime", timeValue);

        // render the triangle
        ourShader.use();



        glBindVertexArray(VAO);


        glm::mat4 trans = glm::mat4(1.0f); //transformation matrix
        //first triangle
        //trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //second triangle
        trans = glm::mat4(1.0f); //reset trans mat
        //trans = glm::scale(trans, glm::vec3(2.0 * glfwGetTime(), 2.0 * glfwGetTime(), 2.0 * glfwGetTime())); //zooming
        //trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        
        
        transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawArrays(GL_TRIANGLES, 0, 3);
     

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}